#include <fstream>
#include <sstream>
#include <string>

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

    loadControlValues();
}

ClassicControlView::~ClassicControlView()
{
    delete ui;
    delete this->kValidator;
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
        ClassicControlView::saveConstantsInFile(kp, ki, kd, FILE_PATH);
        emit message("Datos guardados.", OK);
    } else {
        emit message("No se pudo guardar los datos. Revisar formato", ERROR);
    }
}

void ClassicControlView::loadControlValues(std::string filepath)
{
    std::fstream file(filepath, std::fstream::in);
    // TODO: podría usar un formato estandar como Json o Yaml
    std::string line;
    std::string key;
    std::string value;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> key;
        iss >> value;
        if (key == "kp") {
            this->ui->kp_value->setText(QString(value.c_str()));
        } else if (key == "kd") {
            this->ui->kd_value->setText(QString(value.c_str()));
        } else if (key == "ki") {
            this->ui->ki_value->setText(QString(value.c_str()));
        } else {
            throw Exception("Invalid format of classic control parameters file");
        }
    }
}

void ClassicControlView::instantiate() {
    float targetTemp = this->ui->targetTemperatureTextEdit->text().toFloat();
    float kp = this->ui->kp_value->text().toFloat();
    float kd = this->ui->kd_value->text().toFloat();
    float ki = this->ui->ki_value->text().toFloat();
    this->controlAlgorithm.reset(new ClassicPID(kp, ki, kd, targetTemp, this->sp));
    this->controlAlgorithm->start();
}

const char *ClassicControlView::getName()
{
    return "Clásico";
}
