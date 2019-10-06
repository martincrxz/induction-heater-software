#include "general_view.h"
#include "ui_general_view.h"
#include "../connection/communicator.h"
#include "../connection/protocol/shutdown_message.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    communicator = new Communicator(this);
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
     */
    this->connect(this, &MainWindow::shutdownMessage, communicator, &Communicator::write);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shutdownButton_clicked()
{
    std::shared_ptr<MicroMessage> msg(new ShutdownMessage());
    emit this->shutdownMessage(msg);
}
