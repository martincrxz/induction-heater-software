#include "manual_power_control_view.h"
#include "ui_manual_power_control_view.h"

ManualPowerControlView::ManualPowerControlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualPowerControlView)
{
    ui->setupUi(this);
}

ManualPowerControlView::~ManualPowerControlView()
{
    delete ui;
}
