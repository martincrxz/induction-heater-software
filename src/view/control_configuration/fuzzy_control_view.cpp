#include <QFileDialog>

#include "fuzzy_control_view.h"
#include "ui_fuzzy_control_view.h"

#include "../../control/fuzzy_logic.h"

#define MODE_2x3 0
#define MODE_3x1 1

FuzzyControlView::FuzzyControlView(QWidget *parent, SerialPort *s) :
    ControlConfiguration(parent, s),
    ui(new Ui::FuzzyControlView)
{
    ui->setupUi(this);
    ui->helpbutton->setToolTip("<b>Ayuda:</b><br>"
                               "El modo de operación '2x3' toma el error de temperatura "
                               "y la derivada del error para modificar los valores "
                               "de las constantes kp, kd y ki del control PID clásico. "
                               "Se debe brindar obligatoriamente valores iniciales de "
                               "estas constantes.<br>"
                               "El modo de operación '3x1' toma como entradas "
                               "la temperatura, la derivada y la integral de estas, y "
                               "se actua sobre la potencia de salida.");
    this->kValidator = new QDoubleValidator(-9999, 9999, 2);
    this->tempValidator = new QDoubleValidator(-99999, 99999, 2);
    ui->targetTempLineEdit->setValidator(this->tempValidator);
    ui->kdLineEdit->setValidator(this->kValidator);
    ui->kILineEdit->setValidator(this->kValidator);
    ui->kpLineEdit->setValidator(this->kValidator);
}

FuzzyControlView::~FuzzyControlView()
{
    delete this->ui;
    delete this->kValidator;
    delete this->tempValidator;
}

bool FuzzyControlView::validateInput()
{
    return validateInput(true, this->current_index == MODE_2x3);
}

bool FuzzyControlView::validateInput(bool check_temp, bool pid_mode)
{
    if (this->ui->filenameLabel->text().toStdString() == "") {
        Logger::debug("Config file not selected");
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
            Logger::debug("PID constants failed");
            return false;
        }
        Logger::debug("PID constants check passed");
    }

    if (check_temp) {
        QString targetTemp = this->ui->targetTempLineEdit->text();
        if (targetTemp == "") {
            Logger::debug("Target temperature empty.");
            return false;
        }
        auto tempState = this->tempValidator->validate(targetTemp, d);
        if (tempState != QValidator::Acceptable) {
            Logger::debug("Target temperature check failed.");
            return false;
        }
        Logger::debug("Target temperature check succeed.");
    }

    return true;
}

void FuzzyControlView::instantiate() {
    float targetTemp = this->ui->targetTempLineEdit->text().toFloat();
    std::string filepath = this->ui->filenameLabel->text().toStdString();
    this->controlAlgorithm.reset(new FuzzyLogic(targetTemp, this->sp, filepath, this->window_size));
}

const char *FuzzyControlView::getName()
{
    return "Fuzzy logic";
}

void FuzzyControlView::loadControlValues(std::string filepath) {
    // TODO, refactor
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
