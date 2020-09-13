#include <iostream>
#include <sstream>
#include <logger/logger.h>
#include <QtCore/QDateTime>
#include <cmath>

#include "general_view.h"
#include "ui_general_view.h"
#include "../connection/serialport.h"
#include "../connection/protocol/shutdown_message.h"
#include "../connection/protocol/temperature_reading.h"
#include "../connection/protocol/cold_junction_reading.h"
#include "../connection/protocol/thermocouple_configuration.h"
#include "../connection/protocol/power_set_acknowledge.h"
#include "../connection/protocol/set_manual_control.h"
#include "../connection/protocol/set_automatic_control.h"
#include "../connection/protocol/automatic_control_acknowledge.h"
#include "control_configuration/classic_control_view.h"
#include "../configuration/app_config.h"
#include "../connection/protocol/current_frequency_reading.h"
#include "../connection/protocol/current_RMS_reading.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ApplicationConfig &conf = ApplicationConfig::instance();
    port = new SerialPort(this);
    equipmentView = new EquipmentStatusView(this, this->port);
    automaticView = new AutomaticControlTabView(this, this->port);
    manualPowerView = new ManualPowerControlView(this, this->port);
    autotunningView = new AutoTunningTabView(this, this->port);
    chartView = new ChartTabView(this);
    resetLabelTimer = new QTimer();
    testTimer = new QTimer();
    port->findDevice();

    ui->setupUi(this);
    ui->tabWidget->addTab(equipmentView, "Estado del equipo");
    ui->tabWidget->addTab(automaticView, "Control automático");
    ui->tabWidget->addTab(manualPowerView, "Potencia manual");
    ui->tabWidget->addTab(autotunningView, "Auto-sintonía");
    ui->tabWidget->addTab(chartView, "Gráfico");

    ui->statusValue->setText("OK");
    onManualPowerSet();
    usbOk = false;
    //onStatusChanged();
    onAutomaticPowerSet();
    /**
     * Conecto las distintas señales con los slots
     **/
    connect(port, &SerialPort::shutdownAcknowledge, equipmentView, &EquipmentStatusView::insert);
    connect(ui->thermocoupleTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(thermocoupleChange(int)));
    connect(ui->ovenCommandTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSetManualControl(int)));
    connect(port, SIGNAL(thermocoupleFault(QString,QString)), equipmentView, SLOT(insert(QString,QString)));
    connect(port, &SerialPort::configurationAcknowledge, equipmentView, &EquipmentStatusView::insert);
    connect(port, &SerialPort::temperatureArrived, this, &MainWindow::onTemperatureDataArrived);
    connect(port, &SerialPort::currentFrequencyArrived, this, &MainWindow::onCurrentFrequencyArrived);
    connect(port, &SerialPort::currentRMSArrived, this, &MainWindow::onCurrentRMSArrived);
    connect(port, &SerialPort::coldJunctionArrived, this, &MainWindow::onColdJunctionDataArrived);
    connect(port, SIGNAL(manualControlAcknowledge()), this, SLOT(onManualPowerSet()));
    connect(port, SIGNAL(manualControlAcknowledge(QString,QString)), equipmentView, SLOT(insert(QString,QString)));
    connect(port, SIGNAL(automaticControlAcknowledge()), this, SLOT(onAutomaticPowerSet()));
    connect(port, SIGNAL(automaticControlAcknowledge(QString,QString)), equipmentView, SLOT(insert(QString,QString)));
    connect(port, &SerialPort::powerSetAcknowledge, this, &MainWindow::onPowerSetAckArrived);
    connect(port, &SerialPort::serialPortConnected, this, &MainWindow::onSerialPortConnected);
    connect(port, &SerialPort::serialPortDisconnected, this, &MainWindow::onSerialPortDisconnected);
    connect(this->automaticView, &AutomaticControlTabView::controlAlgorithmDeactivated, this, &MainWindow::onControlTypeChanged);
    connect(this->automaticView, &AutomaticControlTabView::controlAlgorithmActivated, this, &MainWindow::onControlTypeChanged);
    connect(this->autotunningView, &AutoTunningTabView::ZNCalculated, this, &MainWindow::onZNCalculated);
    connect(&conf, &ApplicationConfig::configChanged, this, &MainWindow::configChanged);
    // conecto signals relacionados a la ipmresion de mensajes de notificacion
    connect(this->resetLabelTimer, &QTimer::timeout, this, &MainWindow::resetLabel);
    connect(this->autotunningView, &AutoTunningTabView::printMessage, this, &MainWindow::on_messagePrint);
    connect(this->automaticView, &AutomaticControlTabView::printMessage, this, &MainWindow::on_messagePrint);
    connect(this->manualPowerView, &ManualPowerControlView::printMessage, this, &MainWindow::on_messagePrint);
    /**
     * TEST de injección de datos
     */
#ifdef DEBUG_INJECTION
     connect(this->testTimer, &QTimer::timeout, this, &MainWindow::injectData);
     this->testTimer->start(1000/10.0f);
#endif
     configChanged();
}

#define PI 3.14159265358979323846f
void MainWindow::injectData() {
    float x = chrono.tack();
    if (x > power_step) {
        power_value = qrand() % 100;
        power_step += POWER_STEP_SIZE;
        std::shared_ptr<PowerSetAcknowledge> power(new PowerSetAcknowledge(power_value));
        emit this->port->powerSetAcknowledge(power);
    }

    if (x > freq_step) {
        freq_step += FREQ_STEP_SIZE;
        float delta = qrand() % 5000;
        if (qrand() % 2)
            delta *= -1;
        // La frecuencia mockeada va a ser 20kHz +- x con 
        // -5kHz < x < 5kHz
        std::shared_ptr<CurrentFrequencyReading> frequency(
                new CurrentFrequencyReading(freq_value + delta));
        emit this->port->currentFrequencyArrived(frequency);

    }

    if (x > current_step) {
        current_step += CURRENT_STEP_SIZE;
        float current = amplitude * std::sin(x / 3000.0f * 2.0f * PI);
        std::shared_ptr<CurrentRMSReading> curr_msg(new CurrentRMSReading(current));
        emit this->port->currentRMSArrived(curr_msg);
    }

    if (x > temp_step) {
        amplitude += 50;
        temp_step += STEP_SIZE;
    }

    float temperature = amplitude * std::sin(x / 3000.0f * 2.0f * PI);
    std::shared_ptr<TemperatureReading> temp(new TemperatureReading(temperature));
//    TemperatureReading temp(temperature);
    emit this->port->temperatureArrived(temp);
}

MainWindow::~MainWindow()
{
    this->resetLabelTimer->stop();
    delete this->resetLabelTimer;
    delete ui;
    delete this->testTimer;
}

void MainWindow::on_shutdownButton_clicked()
{
    std::shared_ptr<MicroMessage> msg(new ShutdownMessage());
    port->send(msg);
}

void MainWindow::onTemperatureDataArrived(std::shared_ptr<MicroMessage> msg) {
    auto &temp = (TemperatureReading &) *msg;
    QString currentDatetime = QDateTime::currentDateTime().
            toString("dd/MM/yyyy HH:mm:ss");
    ui->lastTimestampValue->setText(currentDatetime);
    ui->thermocoupleTempValue->setText(QString::number(temp.getData()));
    ui->dut_temp_value->setText(QString::number(temp.getData()));
    Logger::debug("Temperatura recibida: %.2f °C", temp.getData());
    // TODO: debo actualizar el gráfico, como el hilo de control
    // TODO 2: esto quedó horrible, debería haberse llamado a connect
    // en cada proceso que le interesa este mensaje, y que sea autocontenido.
    // acá tengo logica mezclada
    this->chartView->dataAvailable(temp);
    this->automaticView->dataAvailable(temp);
    this->autotunningView->dataAvailable(temp);
}

void MainWindow::onColdJunctionDataArrived(std::shared_ptr<MicroMessage> msg) {
    auto &temp = (ColdJunctionReading &) *msg;
    ui->coldJointTempValue->setText(QString::number(temp.getData()));
    Logger::info("Temperatura de juntura fría: %.2f °C", temp.getData());
}

void MainWindow::onCurrentFrequencyArrived(std::shared_ptr<MicroMessage> msg) {
    auto &freq = (CurrentFrequencyReading &) *msg;
    Logger::debug("Frecuencia recibida: %.2f Hz", freq.getData());
    this->chartView->dataAvailable(freq);
}

void MainWindow::onCurrentRMSArrived(std::shared_ptr<MicroMessage> msg) {
    auto &rms = (CurrentRMSReading &) *msg;
    Logger::debug("Corriente recibida: %.2f A", rms.getData());
    this->chartView->dataAvailable(rms);
}

void MainWindow::thermocoupleChange(int index){
    std::shared_ptr<ThermocoupleConfiguration> configMsg(new ThermocoupleConfiguration());
    configMsg->setType((thermocouple_type_t)index);
    port->send(configMsg);
}

void MainWindow::onPowerSetAckArrived(std::shared_ptr<MicroMessage> msg) {
    auto &pwr = (PowerSetAcknowledge &) *msg;
    this->chartView->dataAvailable(pwr);
    ui->powerValue->setText(QString::number(pwr.getPower()) + " %");
}

void MainWindow::onSetManualControl(int index){
    std::shared_ptr<MicroMessage> msg;
    if (index == 0) {
        msg.reset(new SetManualControl());
    } else {
        msg.reset(new SetAutomaticControl());
        // TODO: borrar esto, lo uso de debug
        // enableAutomaticControlButtons(true);
    }
    port->send(msg);
}

void MainWindow::enableAutomaticControlButtons(bool enable) {
    if (enable)
        Logger::info("Enabling automatic buttons");
    else
        Logger::info("Disabling automatic buttons");
    this->automaticView->enableButtons(enable);
    this->autotunningView->enableButtons(enable);
    this->manualPowerView->enableButtons(enable);
}

void MainWindow::onSerialPortConnected() {
    usbOk = true;
    onStatusChanged();
    resync_microcontroller();
}

void MainWindow::resync_microcontroller() {
    this->thermocoupleChange(this->ui->thermocoupleTypeComboBox->currentIndex());
    this->on_shutdownButton_clicked();
}

void MainWindow::onSerialPortDisconnected() {
    usbOk = false;
    onStatusChanged();
    deactivateProcess();
    on_messagePrint("Se perdió la conexión con el microcontrolador", ERROR, true);
    this->equipmentView->insert(QString::number(0x01), "Microcontrolador desconectado");
}

void MainWindow::deactivateProcess() {
    this->automaticView->stop(false);
    this->autotunningView->stop(false, false);
}

void MainWindow::onStatusChanged(){
    std::string statusMessage;
    if(!usbOk)
        statusMessage = "USB desconectado";
    else if(!thermocoupleOk)
        statusMessage = "Falla en termocupla";
    else
        statusMessage = "OK";
    ui->statusValue->setText(QString::fromStdString(statusMessage));
}

void MainWindow::onManualPowerSet() {
    controlType = MANUAL;
    enableAutomaticControlButtons(false);
    onControlTypeChanged();
}

void MainWindow::onAutomaticPowerSet() {
    controlType = AUTOMATIC;
    enableAutomaticControlButtons(true);
    onControlTypeChanged();
}

void MainWindow::onControlTypeChanged(){
    if (controlType == MANUAL) {
        ui->operationModeValue->setText("MANUAL");
        ui->control_type_value->setText("MANUAL");
        ui->automaticControlValue->setText("OFF");
        this->automaticView->on_deactivateButton_clicked();
    } else {
        ui->operationModeValue->setText("AUTOMATICO");
        ui->control_type_value->setText("AUTOMATICO");
        if (this->automaticView->isControlActivated()) {
            ui->automaticControlValue->setText("ON");
        } else {
            ui->automaticControlValue->setText("OFF");
        }
    }
    ui->current_process->setText(this->automaticView->getProcessName());
}

bool MainWindow::isControlActivated(){
    return automaticView->isControlActivated();
}

void MainWindow::onZNCalculated(float kp, float ki, float kd) {
    std::ostringstream oss;
    oss << "zn-" << QDateTime::currentDateTime().toString("dd-MM-yyyy").toStdString();
    ClassicControlView::saveConstantsInFile(kp, ki, kd, oss.str());
    this->automaticView->loadFile(oss.str());
    this->autotunningView->deactivate(true);
}

void MainWindow::on_messagePrint(const char *str, unsigned char mode, bool reset)
{
    ui->notificationLabel->setText(str);
    if (mode == ERROR){
        ui->notificationLabel->setStyleSheet("QLabel { color : red; }");
    } else if (mode == OK) {
        ui->notificationLabel->setStyleSheet("QLabel { color : green; }");
    } else {
        ui->notificationLabel->setStyleSheet("QLabel { color : black; }");
    }

    if (reset) {
        this->resetLabelTimer->start(3000);
    } else {
        this->resetLabelTimer->stop();
    }
}

void MainWindow::resetLabel() {
    ui->notificationLabel->setText("");
}

void MainWindow::on_actionConfiguration_triggered() {
    confDialog.show();
}

void MainWindow::configChanged() {
    const ApplicationConfig &conf = ApplicationConfig::instance();
    Logger::logLevelChanged(conf.getLogLevel());
    this->automaticView->updateConfig();
}
