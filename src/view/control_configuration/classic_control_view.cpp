#include <fstream>
#include <sstream>
#include <string>
#include <configuration/app_config.h>

#include "messages.h"
#include "logger/logger.h"
#include "exception.h"
#include "classic_control_view.h"
#include "ui_classic_control_view.h"
#include "../../control/classic_pid.h"


ClassicControlView::ClassicControlView(QWidget *parent, SerialPort *sp) :
    ControlConfiguration(parent, sp),
    ui(new Ui::ClassicControlView)
{
    ui->setupUi(this);
    this->kValidator = new QDoubleValidator(-9999, 9999, 2);
    this->tempValidator = new QDoubleValidator(-99999, 99999, 2);
    ui->targetTemperatureTextEdit->setValidator(this->tempValidator);
    ui->kd_value->setValidator(this->kValidator);
    ui->ki_value->setValidator(this->kValidator);
    ui->kp_value->setValidator(this->kValidator);
    updateConfiguration();
}

ClassicControlView::~ClassicControlView()
{
    delete ui;
    delete this->kValidator;
    delete this->tempValidator;
}

bool ClassicControlView::validateInput()
{
    return validateInput(true);
}

bool ClassicControlView::validateInput(bool check_temp)
{
    QString kd = ui->kd_value->text();
    QString ki = ui->ki_value->text();
    QString kp = ui->kp_value->text();
    int d = 0;
    auto kdState = this->kValidator->validate(kd, d);
    auto kiState = this->kValidator->validate(ki, d);
    auto kpState = this->kValidator->validate(kp, d);
    if (check_temp) {
        QString targetTemp = this->ui->targetTemperatureTextEdit->text();
        if (targetTemp == "") {
            return false;
        }
        auto tempState = this->tempValidator->validate(targetTemp, d);
        if (tempState != QValidator::Acceptable) {
            return false;
        }
    }
    if ( kdState != QValidator::Acceptable ||
         kiState != QValidator::Acceptable ||
         kpState != QValidator::Acceptable ) {
        return false;
    }
    return true;
}

void ClassicControlView::on_saveButton_clicked()
{
    if (this->validateInput(false)) {
        float kp = this->ui->kp_value->text().toFloat();
        float ki = this->ui->ki_value->text().toFloat();
        float kd = this->ui->kd_value->text().toFloat();
        ApplicationConfig::instance().saveControlConstant(kp, kd, ki, "classic_pid");
        emit message(CLASSIC_CONTROL_VIEW_DATA_SAVED_MSG, OK, true);
    } else {
        emit message(CLASSIC_CONTROL_SAVE_DATA_FAILED_MSG, ERROR, true);
    }
}

void ClassicControlView::instantiate() {
    float targetTemp = this->ui->targetTemperatureTextEdit->text().toFloat();
    float kp = this->ui->kp_value->text().toFloat();
    float kd = this->ui->kd_value->text().toFloat();
    float ki = this->ui->ki_value->text().toFloat();
    this->controlAlgorithm.reset(new ClassicPID(kp, ki, kd, targetTemp, this->sp, this->window_size));
    this->controlAlgorithm->start();
}

void ClassicControlView::updateConfiguration() {
    std::vector<float> constants = ApplicationConfig::instance().getControlConstants("classic_pid");
    if (constants.size() == 3) {
        this->ui->kp_value->setText(QString::number(constants[0]));
        this->ui->kd_value->setText(QString::number(constants[1]));
        this->ui->ki_value->setText(QString::number(constants[2]));
    }
}

const char *ClassicControlView::getName() {
    return "Clásico";
}
