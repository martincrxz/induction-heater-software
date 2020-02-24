#include <logger/logger.h>
#include "auto_tunning_tab_view.h"
#include "ui_auto_tunning_tab_view.h"
#include "general_view.h"
#include "../connection/protocol/set_power.h"

#define ERROR 1

AutoTunningTabView::AutoTunningTabView(QWidget *parent, SerialPort* port) :
    QWidget(parent),
    ui(new Ui::AutoTunningTabView),
    mainWindow((MainWindow *)parent),
    port(port)
{
    ui->setupUi(this);
    this->resetLabelTimer = new QTimer();
    connect(this->resetLabelTimer, &QTimer::timeout, this, &AutoTunningTabView::resetLabel);
    connect(ui->activateButton, &QPushButton::clicked, this, &AutoTunningTabView::activate);
    connect(ui->deactivateButton, &QPushButton::clicked, this, &AutoTunningTabView::deactivate);
}

AutoTunningTabView::~AutoTunningTabView()
{
    delete ui;
}

void AutoTunningTabView::enableButtons(bool enable) {
	this->ui->activateButton->setEnabled(enable);
	this->ui->deactivateButton->setEnabled(enable);
}

void AutoTunningTabView::activate() {
    if(!mainWindow->isControlActivated() && zn == nullptr) {
        on_messagePrint("Calculando...", 2, false);
        Logger::info(ZN_ACTIVATED_MSG);
        zn.reset(new ZieglerNichols(this, port));
        zn->start();
    }
    else{
        on_messagePrint(ZN_CANT_BE_ACTIVATED_MSG, ERROR);
        Logger::info(ZN_CANT_BE_ACTIVATED_MSG);
    }
}

void AutoTunningTabView::deactivate(bool finished) {
    if (zn == nullptr){
        on_messagePrint("No hay proceso para desactivar", ERROR);
        return;
    }

    zn.reset(nullptr);
    if (finished){
        on_messagePrint(ZN_SUCCESFULY_FINISHED, OK);
        Logger::info(ZN_SUCCESFULY_FINISHED);
    } else {

        on_messagePrint(ZN_INTERRUPTED, ERROR);
        Logger::info(ZN_INTERRUPTED);
    }
}

void AutoTunningTabView::calculateParameters(
        std::vector<std::shared_ptr<TemperatureReading>> &stepResponse) {
    /*
     * Primero, obtengo el máximo de la señal promediando las ultimas
     * muestras estables de la respuesta al escalon
     */
    std::size_t begin = stepResponse.size() - ZN_WINDOW_SIZE - 1;
    float minTemp = stepResponse[0]->getData();
    float maxTemp = 0;
    /**
     * Se sabe que las ultimas ZN_WINDOW_SIZE muestras son todas similares
     * ya que es condición necesaria para que se termine a recepción de
     * muestras.
     */
    for (std::size_t i = begin; i < stepResponse.size(); i++) {
        maxTemp += stepResponse[i]->getData();
    }
    maxTemp /= ZN_WINDOW_SIZE;
    /**
     * Una vez obtenido el maximo, se va a buscar los tiempos en los que se
     * llegue al 10% de la señal, y al 90% de la señal.
     *
     * Esto resulta en una aproximación al calculo de los parámetros por ziegler
     * nichols. Se decidió tomar esta aproximación y no calcular los parámetros
     * por definición debido al costo y la complejidad de buscar el punto de
     * inflexión de la señal (punto donde la derivada segunda valga cero) en
     * forma discreta.
     *
     * TODO: revisar la unidad de los tiempos, ahora están en milis, pero eso
     * puede hacer que las constantes sean muy chicas (tendrían unidad de
     * porcentaje/milis
     */
    std::uint64_t t10 = 0, t90 = 0;
    std::uint64_t t0 = stepResponse[0]->getTimestamp();
    float temp10 = minTemp + (maxTemp - minTemp)* 0.1f;
    float temp90 = minTemp + (maxTemp - minTemp) * 0.9f;
    bool t10Found = false;
    for (auto p : stepResponse) {
        if (p->getData() >= temp10 && !t10Found) {
            t10Found = true;
            t10 = p->getTimestamp() - t0;
        }

        if (p->getData() >= temp90)
            t90 = p->getTimestamp() - t0;
    }
    /*
     * Una vez obtenido t10 y t90, y sabiendo a priori la variación de la señal
     * del horno (10%) y la variación de la señal de temperatura
     * (maxTemp - minTemp), se procede a calcular los parámetros de control,
     * que se guardarán en un archivo para su posterior uso.
     *
     * kp= 1.2 * k0
     * ki = 0.60*Ko/T10
     * kd = 0.60*Ko*T110
     */
    float k0 = 10.0f * t90 / ((maxTemp - minTemp) * t10);
    float kp, ki, kd;
    kp = 1.2f * k0;         // [kp] = % / °C
    ki = 0.6f * k0/t10;     // [ki] = % / (ms * °C)
    kd = 0.6f * k0 * t10;   // [kd] = % * ms / °C
    emit ZNCalculated(kp, ki, kd);
}

void AutoTunningTabView::on_messagePrint(const char *str, unsigned char mode, bool reset)
{
    ui->status_label->setText(str);
    if (mode == ERROR){
        ui->status_label->setStyleSheet("QLabel { color : red; }");
    } else if (mode == OK) {
        ui->status_label->setStyleSheet("QLabel { color : green; }");
    } else {
        ui->status_label->setStyleSheet("QLabel { color : black; }");
    }

    if (reset){
        this->resetLabelTimer->start(3000);
    } else {
        this->resetLabelTimer->stop();
    }
}

void AutoTunningTabView::resetLabel() {
    ui->status_label->setText("");
}
