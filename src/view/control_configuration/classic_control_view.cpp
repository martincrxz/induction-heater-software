#include <fstream>
#include <sstream>
#include <string>
#include <configuration/app_config.h>
#include <QtWidgets/QInputDialog>

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
    this->selectedPresetName = getName();
    updateConfiguration();
    connect(&ApplicationConfig::instance(), &ApplicationConfig::algorithmConstantChanged, this, &ClassicControlView::updateConfiguration);
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
        bool ok;
        QString presetName = QInputDialog::getText(this, tr("Seleccione nombre de configuración"),
                                                   tr("Nombre del preset:"), QLineEdit::Normal,
                                                   "", &ok);
        if (ok && !presetName.isEmpty()) {
            this->selectedPresetName = presetName.toStdString();
            ApplicationConfig::instance().saveControlConstant(kp, kd, ki, presetName.toStdString().c_str());
            emit message(CLASSIC_CONTROL_VIEW_DATA_SAVED_MSG, OK, true);
        }
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

const char *ClassicControlView::getName() {
    return PID_CONTROL_NAME;
}

void ClassicControlView::on_constantsPresetCombo_currentIndexChanged(const QString &presetSelected) {
    setPresetConfiguration(presetSelected.toStdString().c_str());
}

void ClassicControlView::loadPresetList(const char *currentPreset) {
    std::list<QString> presets = ApplicationConfig::instance().getPresetList();
    this->ui->constantsPresetCombo->clear();
    this->ui->constantsPresetCombo->addItem(EMPTY_PRESET_LABEL);
    int i = 1;
    for (auto &presetName: presets) {
        this->ui->constantsPresetCombo->addItem(presetName);
        if (presetName == currentPreset) {
            this->ui->constantsPresetCombo->setCurrentIndex(i);
        }
        i++;
    }
}

void ClassicControlView::setPresetConfiguration(const char *currentPreset) {
    std::vector<float> constants = ApplicationConfig::instance().getControlConstants(currentPreset);
    if (constants.size() == 3) {
        this->selectedPresetName = currentPreset;
        this->ui->kp_value->setText(QString::number(constants[0]));
        this->ui->kd_value->setText(QString::number(constants[1]));
        this->ui->ki_value->setText(QString::number(constants[2]));
    } else {
        this->ui->kp_value->setText("");
        this->ui->kd_value->setText("");
        this->ui->ki_value->setText("");
    }
}

void ClassicControlView::updateConfiguration() {
    this->_updateConfiguration(this->selectedPresetName.c_str());
}

void ClassicControlView::_updateConfiguration(const char *currentPreset) {
    this->loadPresetList(currentPreset);
    this->setPresetConfiguration(currentPreset);
}
