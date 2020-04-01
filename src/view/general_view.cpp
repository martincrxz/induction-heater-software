#include <iostream>
#include <sstream>
#include <logger/logger.h>
#include <QtCore/QDateTime>

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    port = new SerialPort(this);
    equipmentView = new EquipmentStatusView(this, this->port);
    automaticView = new AutomaticControlTabView(this, this->port);
    manualPowerView = new ManualPowerControlView(this, this->port);
    autotunningView = new AutoTunningTabView(this, this->port);
    chartView = new ChartTabView(this);
    resetLabelTimer = new QTimer();
    port->findDevice();

    ui->setupUi(this);
    ui->tabWidget->addTab(equipmentView, "Estado del equipo");
    ui->tabWidget->addTab(automaticView, "Control automático");
    ui->tabWidget->addTab(manualPowerView, "Potencia manual");
    ui->tabWidget->addTab(autotunningView, "Auto-sintonía");
    ui->tabWidget->addTab(chartView, "Gráfico");

    ui->statusValue->setText("OK");
    onManualPowerSet();
    //onAutomaticPowerSet();
    /**
     * Conecto las distintas señales con los slots
     **/
    connect(port, &SerialPort::shutdownAcknowledge, equipmentView, &EquipmentStatusView::insert);
    connect(ui->thermocoupleTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(thermocoupleChange(int)));
    connect(ui->ovenCommandTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSetManualControl(int)));
    connect(port, SIGNAL(thermocoupleFault(QString,QString)), equipmentView, SLOT(insert(QString,QString)));
    connect(port, &SerialPort::configurationAcknowledge, equipmentView, &EquipmentStatusView::insert);
    connect(port, &SerialPort::temperatureArrived, this, &MainWindow::onTemperatureDataArrived);
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
    // conecto signals relacionados a la ipmresion de mensajes de notificacion
    connect(this->resetLabelTimer, &QTimer::timeout, this, &MainWindow::resetLabel);
    connect(this->autotunningView, &AutoTunningTabView::printMessage, this, &MainWindow::on_messagePrint);
    connect(this->automaticView, &AutomaticControlTabView::printMessage, this, &MainWindow::on_messagePrint);
    connect(this->manualPowerView, &ManualPowerControlView::printMessage, this, &MainWindow::on_messagePrint);
}

MainWindow::~MainWindow()
{
    this->resetLabelTimer->stop();
    delete this->resetLabelTimer;
    delete ui;
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
    Logger::info("Temperatura recibida: %.2f °C", temp.getData());
    // TODO: debo actualizar el gráfico, como el hilo de control
    this->chartView->dataAvailable(temp);
    this->automaticView->dataAvailable(temp);
    ui->dut_temp_value->setText(QString::number(temp.getData()));
}

void MainWindow::onColdJunctionDataArrived(std::shared_ptr<MicroMessage> msg) {
    auto &temp = (ColdJunctionReading &) *msg;
    ui->coldJointTempValue->setText(QString::number(temp.getData()));
    Logger::info("Temperatura de juntura fría: %.2f °C", temp.getData());
}

void MainWindow::thermocoupleChange(int index){
    std::shared_ptr<ThermocoupleConfiguration> configMsg(new ThermocoupleConfiguration());
    configMsg->setType((thermocouple_type_t)index);
    port->send(configMsg);
}

void MainWindow::onPowerSetAckArrived(std::shared_ptr<MicroMessage> msg) {
    auto &temp = (PowerSetAcknowledge &) *msg;
    this->chartView->dataAvailable(temp);
    ui->powerValue->setText(QString::number(temp.getPower()) + " %");
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
}

void MainWindow::onSerialPortDisconnected() {
    usbOk = false;
    onStatusChanged();
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
