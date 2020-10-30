#include <QFileDialog>
#include <QtWidgets/QInputDialog>
#include "messages.h"

#include "fuzzy_control_view.h"
#include "configuration/app_config.h"
#include "ui_fuzzy_control_view.h"
#include "logger/logger.h"
#include "../../control/fuzzy2x3.h"
#include "../../control/fuzzy3x1.h"

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
    ui->targetTempLineEdit->setValidator(this->tempValidator);
    ui->kdLineEdit->setValidator(this->kValidator);
    ui->kILineEdit->setValidator(this->kValidator);
    ui->kpLineEdit->setValidator(this->kValidator);
    this->selectedPresetName = getName();
    updateConfiguration();
    connect(&ApplicationConfig::instance(), &ApplicationConfig::algorithmConstantChanged, this, &FuzzyControlView::updateConfiguration);
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
    int d = 0;
    if (pid_mode) {
        auto kdState = this->kValidator->validate(kd, d);
        auto kiState = this->kValidator->validate(ki, d);
        auto kpState = this->kValidator->validate(kp, d);

        if ( kdState != QValidator::Acceptable ||
             kiState != QValidator::Acceptable ||
             kpState != QValidator::Acceptable ) {
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
    if (current_index == MODE_2x3)
        this->controlAlgorithm.reset(new Fuzzy2x3(targetTemp, this->sp, filepath, this->window_size));
    else 
        this->controlAlgorithm.reset(new Fuzzy3x1(targetTemp, this->sp, filepath, this->window_size));
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
    } else {
        this->ui->kdLabel->show();
        this->ui->kpLabel->show();
        this->ui->kiLabel->show();
        this->ui->kdLineEdit->show();
        this->ui->kpLineEdit->show();
        this->ui->kILineEdit->show();
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
