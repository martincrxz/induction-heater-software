#include <logger/logger.h>
#include "auto_tunning_tab_view.h"
#include "ui_auto_tunning_tab_view.h"
#include "general_view.h"
#include "../connection/protocol/set_power.h"

AutoTunningTabView::AutoTunningTabView(QWidget *parent, SerialPort* port) :
    QWidget(parent),
    ui(new Ui::AutoTunningTabView),
    mainWindow((MainWindow *)parent),
    port(port)
{
    ui->setupUi(this);

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
    if(!mainWindow->isControlActivated()) {
        Logger::info("Se activo el ZN");
        zn.reset(new ZieglerNichols(port));
        zn->start();
    }
    else
        Logger::info("Se quiere activar el ZN pero hay un control activo");
}

void AutoTunningTabView::deactivate() {
    zn.reset(nullptr);
    Logger::info("Se interrumpe ZN");
}