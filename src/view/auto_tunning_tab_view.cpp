#include "auto_tunning_tab_view.h"
#include "ui_auto_tunning_tab_view.h"

AutoTunningTabView::AutoTunningTabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoTunningTabView)
{
    ui->setupUi(this);
}

AutoTunningTabView::~AutoTunningTabView()
{
    delete ui;
}

void AutoTunningTabView::enableButtons(bool enable) {
	this->ui->activateButton->setEnabled(enable);
	this->ui->deactivateButton->setEnabled(enable);
}