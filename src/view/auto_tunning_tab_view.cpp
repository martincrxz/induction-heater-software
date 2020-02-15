#include <logger/logger.h>
#include "auto_tunning_tab_view.h"
#include "ui_auto_tunning_tab_view.h"
#include "general_view.h"

AutoTunningTabView::AutoTunningTabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoTunningTabView),
    mainWindow((MainWindow *)parent)
{
    ui->setupUi(this);

    connect(ui->activateButton, &QPushButton::clicked, this, &AutoTunningTabView::activate);
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
    if(!mainWindow->isControlActivated())
        Logger::info("Se activo el ZN");
    else
        Logger::info("Se quiere activar el ZN pero hay un control activo");
}

