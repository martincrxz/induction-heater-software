#include <logger/logger.h>
#include "auto_tunning_tab_view.h"
#include "ui_auto_tunning_tab_view.h"
#include "general_view.h"
#include "../connection/protocol/set_power.h"
#include "message_modes.h"

AutoTunningTabView::AutoTunningTabView(QWidget *parent, SerialPort* port) :
    QWidget(parent),
    ui(new Ui::AutoTunningTabView),
    mainWindow((MainWindow *)parent),
    port(port)
{
    ui->setupUi(this);
    this->powerValidator = new QIntValidator(0, 100);
    this->tempValidator = new QDoubleValidator(-99999, 99999, 2);
    this->ui->cutoff_temperature->setValidator(this->tempValidator);
    this->ui->initial_power->setValidator(this->powerValidator);
    this->ui->stationary_power->setValidator(this->powerValidator);
    connect(ui->activateButton, &QPushButton::clicked, this, &AutoTunningTabView::activate);
    connect(ui->deactivateButton, &QPushButton::clicked, this, &AutoTunningTabView::deactivate);
}

AutoTunningTabView::~AutoTunningTabView()
{
    delete this->powerValidator;
    delete this->tempValidator;
    delete ui;
}

bool AutoTunningTabView::validateInput() {
    QString initial_power = this->ui->initial_power->text();
    QString stationary_power = this->ui->stationary_power->text();
    QString cutoff_temp = this->ui->cutoff_temperature->text();
    if (initial_power == "" || stationary_power == "" || cutoff_temp == "")
        return false;

    int d = 0;
    auto ipower_state = this->powerValidator->validate(initial_power, d);
    auto spower_state = this->powerValidator->validate(stationary_power, d);
    auto ctemp_state = this->tempValidator->validate(cutoff_temp, d);

    if ( ipower_state != QValidator::Acceptable ||
         spower_state != QValidator::Acceptable ||
         ctemp_state != QValidator::Acceptable )
        return false;

    if (initial_power.toInt() >= stationary_power.toInt())
        return false;

    return true;
}

void AutoTunningTabView::enableButtons(bool enable) {
    this->ui->activateButton->setEnabled(enable);
	this->ui->deactivateButton->setEnabled(enable);
}

void AutoTunningTabView::activate() {
    if(!mainWindow->isControlActivated() && zn == nullptr) {
        if (!validateInput()) {
            emit printMessage("Error en los parámetros.", ERROR, true);
            Logger::info("Bad arguments");
            return;
        }
        emit printMessage("Calculando...", 2, false);
        Logger::info(ZN_ACTIVATED_MSG);
        int initial_power = this->ui->initial_power->text().toInt();
        int stationary_power = this->ui->stationary_power->text().toInt();
        float cutoff_temp = this->ui->cutoff_temperature->text().toFloat();
        Logger::info("ipower: %i, spower: %i, ctemp, %f", initial_power, stationary_power, cutoff_temp);
        zn.reset(new ZieglerNichols(this, initial_power, stationary_power, cutoff_temp, port));
        zn->start();
    } else{
        emit printMessage(ZN_CANT_BE_ACTIVATED_MSG, ERROR, true);
        Logger::info(ZN_CANT_BE_ACTIVATED_MSG);
    }
}

void AutoTunningTabView::deactivate(bool finished) {
    this->stop(finished, true);
}

void AutoTunningTabView::stop(bool finished, bool printError) {
    if (zn == nullptr) {
        if (printError)
            emit printMessage("No hay proceso para desactivar", ERROR, true);
        return;
    }

    zn.reset(nullptr);
    if (finished) {
        emit printMessage(ZN_SUCCESFULY_FINISHED, OK, true);
        Logger::info(ZN_SUCCESFULY_FINISHED);
    } else {
        emit printMessage(ZN_INTERRUPTED, ERROR, true);
        Logger::info(ZN_INTERRUPTED);
    }
}

void AutoTunningTabView::autotunningFailed(const char *msg) {
    emit printMessage(msg, ERROR, true);
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
