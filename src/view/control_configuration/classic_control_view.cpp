#include <fstream>
#include <sstream>
#include <string>

#include "logger/logger.h"
#include "exception.h"
#include "classic_control_view.h"
#include "ui_classic_control_view.h"
#include "../../control/classic_pid.h"


ClassicControlView::ClassicControlView(QWidget *parent) :
    ControlConfiguration(parent),
    ui(new Ui::ClassicControlView)
{
    ui->setupUi(this);
    this->kdValidator = new QDoubleValidator(-9999, 9999, 2);
    this->kiValidator = new QDoubleValidator(-9999, 9999, 2);
    this->kpValidator = new QDoubleValidator(-9999, 9999, 2);
    ui->kd_value->setValidator(this->kdValidator);
    ui->ki_value->setValidator(this->kiValidator);
    ui->kp_value->setValidator(this->kpValidator);

   loadControlValues();
}

ClassicControlView::~ClassicControlView()
{
    delete ui;
    delete this->kdValidator;
    delete this->kiValidator;
    delete this->kpValidator;
}

bool ClassicControlView::validateInput()
{
    QString kd = ui->kd_value->text();
    QString ki = ui->ki_value->text();
    QString kp = ui->kp_value->text();
    int d = 0;
    auto validator = ui->kd_value->validator();
    auto kdState = validator->validate(kd, d);
    auto kiState = validator->validate(ki, d);
    auto kpState = validator->validate(kp, d);

    if ( kdState != QValidator::Acceptable ||
         kiState != QValidator::Acceptable ||
         kpState != QValidator::Acceptable ) {
        return false;
    }

    return true;
}

void ClassicControlView::on_saveButton_clicked()
{
    if (this->validateInput()) {
        std::fstream file(FILE_PATH, std::fstream::out |
                          std::fstream::trunc);
        file << "kp " << this->ui->kp_value->text().toStdString() << std::endl;
        file << "kd " << this->ui->kd_value->text().toStdString() << std::endl;
        file << "ki " << this->ui->ki_value->text().toStdString() << std::endl;

        std::ostringstream oss;
        oss << "Data saved in file: " << FILE_PATH;
        Logger::info(oss.str());
        emit message("Datos guardados.", OK);
    } else {
        emit message("No se pudo guardar los datos. Revisar formato", ERROR);
    }
}

void ClassicControlView::loadControlValues()
{
    std::fstream file(FILE_PATH, std::fstream::in);
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
    float kp = this->ui->kp_value->text().toFloat();
    float kd = this->ui->kd_value->text().toFloat();
    float ki = this->ui->ki_value->text().toFloat();
    this->controlAlgorithm.reset(new ClassicPID(kp, ki, kd));
}
