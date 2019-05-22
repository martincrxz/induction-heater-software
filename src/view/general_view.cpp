#include "general_view.h"
#include "ui_general_view.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(&equipmentView, "Estado del equipo");
    ui->tabWidget->addTab(&automaticView, "Control automático");
    ui->tabWidget->addTab(&manualPowerView, "Potencia manual");
}

MainWindow::~MainWindow()
{
    delete ui;
}
