#include <logger/logger.h>
#include "messages.h"
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

void AutoTunningTabView::dataAvailable(TemperatureReading &temp) {
    if (zn != nullptr) {
        zn->receiveData(temp);
    }
}

void AutoTunningTabView::activate() {
    if(!mainWindow->isControlActivated() && zn == nullptr) {
        if (!validateInput()) {
            emit printMessage(AUTOTUNNING_VIEW_BAD_ARGUMENTS, ERROR, true);
            Logger::info(AUTOTUNNING_VIEW_BAD_ARGUMENTS);
            return;
        }
        emit printMessage(AUTOTUNING_VIEW_PROCESSING_MSG, 2, false);
        Logger::info(ZN_ACTIVATED_MSG);
        int initial_power = this->ui->initial_power->text().toInt();
        int stationary_power = this->ui->stationary_power->text().toInt();
        float cutoff_temp = this->ui->cutoff_temperature->text().toFloat();
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
            emit printMessage(AUTOTUNNING_NO_PROCEES_TO_DEACTIVATE_MSG, ERROR, true);
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

void AutoTunningTabView::znCalculated(float &kp, float &kd, float &ki) {
    emit ZNCalculated(kp, ki, kd);
}
