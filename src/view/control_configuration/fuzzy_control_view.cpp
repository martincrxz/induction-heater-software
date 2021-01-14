#include <QFileDialog>
#include <QtWidgets/QInputDialog>
#include <memory>
#include "messages.h"

#include "fuzzy_control_view.h"
#include "configuration/app_config.h"
#include "ui_fuzzy_control_view.h"
#include "logger/logger.h"
#include "control/fuzzy2x3.h"
#include "control/fuzzy2x1.h"
#include "control/fuzzy_logic.h"

#define MODE_2x3 0
#define MODE_3x1 1

FuzzyControlView::FuzzyControlView(QWidget *parent, SerialPort *s) :
    ControlConfiguration(parent, s),
    ui(new Ui::FuzzyControlView)
{
    ui->setupUi(this);
    ui->helpbutton->setToolTip(FUZZY_CONTROL_VIEW_TYPE_TOOLTIP_MSG);
    this->kValidator = new QDoubleValidator(-9999, 9999, 2);
    this->tempValidator = new QDoubleValidator(-99999, 99999, 2);
    this->sensitivityValidator = new QDoubleValidator(0, 10000, 2);

    ui->targetTempLineEdit->setValidator(this->tempValidator);
    ui->kdLineEdit->setValidator(this->kValidator);
    ui->kILineEdit->setValidator(this->kValidator);
    ui->kpLineEdit->setValidator(this->kValidator);
    ui->ki_sensitivity->setValidator(this->sensitivityValidator);
    ui->kp_sensitivity->setValidator(this->sensitivityValidator);
    ui->kd_sensitivity->setValidator(this->sensitivityValidator);
    ui->error_sensitivity->setValidator(this->sensitivityValidator);
    ui->derivative_error_sensitivity->setValidator(this->sensitivityValidator);
    ui->output_sensitivity->setValidator(this->sensitivityValidator);

    this->selectedPresetName = getName();
    updateConfiguration();
    connect(&ApplicationConfig::instance(), &ApplicationConfig::algorithmConstantChanged, this, &FuzzyControlView::updateConfiguration);
    this->ui->output_s_label->hide();
    this->ui->output_sensitivity->hide();
    
    this->ui->error_sensitivity->setText(QString::number(ERROR_SENSITIVITY_DEFAULT_VALUE_2x3));
    this->ui->derivative_error_sensitivity->setText(QString::number(ERROR_DERIVATIVE_SENSITIVITY_DEFAULT_VALUE_2x3));
    this->ui->output_sensitivity->setText(QString::number(OUTPUT_SENSITIVITY_DEFAULT_VALUE_2x1));
    this->ui->kp_sensitivity->setText(QString::number(KP_SENSITIVITY_DEFAULT_VALUE_2x3));
    this->ui->kd_sensitivity->setText(QString::number(KD_SENSITIVITY_DEFAULT_VALUE_2x3));
    this->ui->ki_sensitivity->setText(QString::number(KI_SENSITIVITY_DEFAULT_VALUE_2x3));
}

FuzzyControlView::~FuzzyControlView()
{
    delete this->ui;
    delete this->kValidator;
    delete this->tempValidator;
}

bool FuzzyControlView::validateInput()
{
    return validateInput(true, this->current_index == MODE_2x3, true);
}

bool FuzzyControlView::validateInput(bool check_temp, bool pid_mode, bool check_file)
{
    if (check_file && this->ui->filenameLabel->text().toStdString() == "") {
        Logger::debug(CONFIG_FILE_NOT_SELECTED);
        return false;
    }

    QString kd = ui->kdLineEdit->text();
    QString ki = ui->kILineEdit->text();
    QString kp = ui->kpLineEdit->text();
    QString kis = ui->ki_sensitivity->text();
    QString kps = ui->kp_sensitivity->text();
    QString kds = ui->kd_sensitivity->text();
    QString es  = ui->error_sensitivity->text();
    QString des = ui->derivative_error_sensitivity->text();
    QString os  = ui->output_sensitivity->text();
    int d = 0;
    if (pid_mode) {
        auto kdState = this->kValidator->validate(kd, d);
        auto kiState = this->kValidator->validate(ki, d);
        auto kpState = this->kValidator->validate(kp, d);

        auto kisState = this->sensitivityValidator->validate(kis, d);
        auto kdsState = this->sensitivityValidator->validate(kds, d);
        auto esState  = this->sensitivityValidator->validate(es, d);
        auto desState = this->sensitivityValidator->validate(des, d);
        auto kpsState = this->sensitivityValidator->validate(kps, d);

        if ( kdState != QValidator::Acceptable ||
             kiState != QValidator::Acceptable ||
             kpState != QValidator::Acceptable ||
             kisState != QValidator::Acceptable ||
             kdsState != QValidator::Acceptable ||
             kpsState != QValidator::Acceptable ||
             esState  != QValidator::Acceptable ||
             desState != QValidator::Acceptable ) {
            Logger::debug(FUZZY_CONTROL_VIEW_PID_BAD_FORMAT);
            return false;
        }
        Logger::debug(FUZZY_CONTROL_VIEW_CONSTANTS_OK_MSG);
    } else {
        auto osState  = this->sensitivityValidator->validate(os, d);
        auto esState  = this->sensitivityValidator->validate(es, d);
        auto desState = this->sensitivityValidator->validate(des, d);
        if (osState  != QValidator::Acceptable ||
            esState  != QValidator::Acceptable ||
            desState != QValidator::Acceptable) {
            Logger::debug(FUZZY_CONTROL_VIEW_PID_BAD_FORMAT);
            return false;
        }
        Logger::debug(FUZZY_CONTROL_VIEW_CONSTANTS_OK_MSG);
    }

    if (check_temp) {
        QString targetTemp = this->ui->targetTempLineEdit->text();
        if (targetTemp == "") {
            Logger::debug(FUZZY_CONTROL_TEMPERATURE_NOT_SET_ERROR_MSG);
            return false;
        }
        auto tempState = this->tempValidator->validate(targetTemp, d);
        if (tempState != QValidator::Acceptable) {
            Logger::debug(FUZZY_CONTROL_TARGET_TEMP_CHECK_FAILED_MSG);
            return false;
        }
        Logger::debug(FUZZY_CONTROL_VIEW_TARGET_CHECK_SUCCED_MSG);
    }

    return true;
}

void FuzzyControlView::instantiate() {
    float targetTemp = this->ui->targetTempLineEdit->text().toFloat();
    std::string filepath = this->ui->filenameLabel->text().toStdString();
    float error_s = this->ui->error_sensitivity->text().toFloat();
    float d_error_s = this->ui->derivative_error_sensitivity->text().toFloat();
    float deadzone = this->ui->deadzoneLineEdit->text().toFloat();
    if (current_index == MODE_2x3) {
        float kp = this->ui->kpLineEdit->text().toFloat();
        float ki = this->ui->kILineEdit->text().toFloat();
        float kd = this->ui->kdLineEdit->text().toFloat();
        float kp_s = this->ui->kp_sensitivity->text().toFloat();
        float kd_s = this->ui->kd_sensitivity->text().toFloat();
        float ki_s = this->ui->ki_sensitivity->text().toFloat();
        this->controlAlgorithm.reset(new Fuzzy2x3(targetTemp, deadzone, kp, kd, ki, this->sp, filepath, this->window_size,
                                                  error_s, d_error_s, kp_s, ki_s, kd_s));
    } else {
        float out_s = this->ui->output_sensitivity->text().toFloat();
        this->controlAlgorithm.reset(new Fuzzy2x1(targetTemp, deadzone, this->sp, filepath, this->window_size,
                                                  error_s, d_error_s, out_s));
    }
}

const char *FuzzyControlView::getName()
{
    return FUZZY_2x3_NAME;
}

void FuzzyControlView::on_operationModeCombo_currentIndexChanged(int index)
{
    this->current_index = index;
    // Si selecciono un modo que no sea 3 salidas (las constantes de
    // control clásico) entonces oculto los line edit de las constantes
    // iniciales.
    if (index != MODE_2x3) {
        this->ui->kdLabel->hide();
        this->ui->kpLabel->hide();
        this->ui->kiLabel->hide();
        this->ui->kdLineEdit->hide();
        this->ui->kpLineEdit->hide();
        this->ui->kILineEdit->hide();
        this->ui->ki_sensitivity_label->hide();
        this->ui->kp_sensitivity_label->hide();
        this->ui->kd_sensitivity_label->hide();
        this->ui->ki_sensitivity->hide();
        this->ui->kp_sensitivity->hide();
        this->ui->kd_sensitivity->hide();
        this->ui->output_s_label->show();
        this->ui->output_sensitivity->show();
    } else {
        this->ui->kdLabel->show();
        this->ui->kpLabel->show();
        this->ui->kiLabel->show();
        this->ui->kdLineEdit->show();
        this->ui->kpLineEdit->show();
        this->ui->kILineEdit->show();
        this->ui->ki_sensitivity_label->show();
        this->ui->kp_sensitivity_label->show();
        this->ui->kd_sensitivity_label->show();
        this->ui->ki_sensitivity->show();
        this->ui->kp_sensitivity->show();
        this->ui->kd_sensitivity->show();
        this->ui->output_s_label->hide();
        this->ui->output_sensitivity->hide();
    }
}

void FuzzyControlView::on_openFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Seleccione archivo de control", "", "*.json");
    this->ui->filenameLabel->setText(filename);
}

void FuzzyControlView::on_save_button_clicked()
{
    if (this->current_index == MODE_2x3) {
        if (this->validateInput(false, true, false)) {
            float kp = this->ui->kpLineEdit->text().toFloat();
            float ki = this->ui->kILineEdit->text().toFloat();
            float kd = this->ui->kdLineEdit->text().toFloat();
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
}

void FuzzyControlView::on_constantsPresetCombo_currentIndexChanged(const QString &presetSelected) {
    setPresetConfiguration(presetSelected.toStdString().c_str());
}

void FuzzyControlView::loadPresetList(const char *currentPreset) {
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

void FuzzyControlView::setPresetConfiguration(const char *currentPreset) {
    std::vector<float> constants = ApplicationConfig::instance().getControlConstants(currentPreset);
    if (constants.size() == 3) {
        this->selectedPresetName = currentPreset;
        this->ui->kpLineEdit->setText(QString::number(constants[0]));
        this->ui->kdLineEdit->setText(QString::number(constants[1]));
        this->ui->kILineEdit->setText(QString::number(constants[2]));
    } else {
        this->ui->kpLineEdit->setText("");
        this->ui->kdLineEdit->setText("");
        this->ui->kILineEdit->setText("");
    }
}

void FuzzyControlView::updateConfiguration() {
    this->_updateConfiguration(this->selectedPresetName.c_str());
}

void FuzzyControlView::_updateConfiguration(const char *currentPreset) {
    this->loadPresetList(currentPreset);
    this->setPresetConfiguration(currentPreset);
}
