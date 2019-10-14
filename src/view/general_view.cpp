#include <logger/logger.h>
#include "general_view.h"
#include "ui_general_view.h"
#include "../connection/serialport.h"
#include "../connection/protocol/shutdown_message.h"
#include "../connection/protocol/temperature_reading.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    port = new SerialPort(this);
    equipmentView = new EquipmentStatusView(this);
    automaticView = new AutomaticControlTabView(this);
    manualPowerView = new ManualPowerControlView(this);
    autotunningView = new AutoTunningTabView(this);
    chartView = new ChartTabView(this);

    ui->setupUi(this);
    ui->tabWidget->addTab(equipmentView, "Estado del equipo");
    ui->tabWidget->addTab(automaticView, "Control automático");
    ui->tabWidget->addTab(manualPowerView, "Potencia manual");
    ui->tabWidget->addTab(autotunningView, "Auto-sintonía");
    ui->tabWidget->addTab(chartView, "Gráfico");

    /**
     * Conecto las distintas señales con los slots
     **/
    connect(this, &MainWindow::shutdownMessage, port, &SerialPort::send);
    connect(port, &SerialPort::shutdownAcknowledge, equipmentView, &EquipmentStatusView::insert);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onShutdownButtonClicked()
{
    std::shared_ptr<MicroMessage> msg(new ShutdownMessage());
    emit this->shutdownMessage(msg);
}

void MainWindow::onTemperatureDataArrived(std::shared_ptr<MicroMessage> msg) {
    auto &temp = (TemperatureReading &) *msg;
    std::string log("Temperatura recibida: ");
    log += temp.getData();
    log += " °C";
    Logger::info(log);
    // TODO: debo actualizar el gráfico, como el hilo de control
    this->chartView->dataAvailable(temp);
}
