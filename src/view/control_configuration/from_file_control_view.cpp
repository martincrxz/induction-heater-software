#include <fstream>
#include <logger/logger.h>
#include <QFileDialog>
#include <string>
#include <sstream>

#include "../../control/file_control.h"
#include "from_file_control_view.h"
#include "ui_from_file_control_view.h"
// TODO: wrappear el formulario de ki,kd.kp en un componente propio y unico
// para todas las vistas. (prioridad baja)
FromFileControlView::FromFileControlView(QWidget *parent, SerialPort *s) :
    ControlConfiguration(parent, s),
    ui(new Ui::FromFileControlView)
{
    ui->setupUi(this);
    this->kValidator = new QDoubleValidator(-9999, 9999, 2);
    ui->kdLineEdit->setValidator(this->kValidator);
    ui->kiLineEdit->setValidator(this->kValidator);
    ui->kpLineEdit->setValidator(this->kValidator);

    loadControlValues();
}

FromFileControlView::~FromFileControlView()
{
    delete ui;
    delete this->kValidator;
}

bool FromFileControlView::validateInput()
{
    QString kd = ui->kdLineEdit->text();
    QString ki = ui->kiLineEdit->text();
    QString kp = ui->kpLineEdit->text();
    int d = 0;
    auto kdState = this->kValidator->validate(kd, d);
    auto kiState = this->kValidator->validate(ki, d);
    auto kpState = this->kValidator->validate(kp, d);
    if ( kdState != QValidator::Acceptable ||
         kiState != QValidator::Acceptable ||
         kpState != QValidator::Acceptable ) {
        return false;
    }
    return true;
}

void FromFileControlView::instantiate() {
    float kp = this->ui->kpLineEdit->text().toFloat();
    float kd = this->ui->kdLineEdit->text().toFloat();
    float ki = this->ui->kiLineEdit->text().toFloat();
    this->controlAlgorithm.reset(new FileControl(kp, ki, kd, controlDirectives, this->sp));
    this->controlAlgorithm->start();
}

const char *FromFileControlView::getName()
{
    return "Desde archivo";
}

void FromFileControlView::on_openFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Seleccione archivo de control", "", "*.csv");
    this->ui->filenameLabel->setText(filename);
    if (filename != "") {
        parseFile();
    }
}

void FromFileControlView::on_saveButton_clicked()
{
    if (this->validateInput()) {
        std::fstream file(FILE_PATH, std::fstream::out |
                          std::fstream::trunc);
        file << "kp " << this->ui->kpLineEdit->text().toStdString() << std::endl;
        file << "kd " << this->ui->kdLineEdit->text().toStdString() << std::endl;
        file << "ki " << this->ui->kiLineEdit->text().toStdString() << std::endl;

        Logger::info("Data saved in file: %s", FILE_PATH);
        emit message("Parámetros de control guardados.", OK);
    } else {
        emit message("No se pudo guardar los parámetros de control. Revisar formato", ERROR);
    }
}

void FromFileControlView::parseFile() {
    try {
        std::string filename = this->ui->filenameLabel->text().toStdString();
        Logger::debug("Loading file: %s", filename.c_str());
        std::fstream file(filename);
        if (!file.is_open()) {
            this->message("El archivo no existe", ERROR);
            return;
        }
        std::string line;
        std::string strValue;
        std::int32_t aux;
        std::vector<std::vector<std::uint32_t>> config;
        /**
         * El archivo debe tener la siguiente forma
         *
         * tiempo_en_segundos;temp_objetivo;potencia
         *
         * Ejemplo:
         *
         * 45;800;90
         * 30;1200;40
         * 10;1300;0
         *
         * Como condiciones se debe pedir que la potencia sea un entero entre
         * 0 y 100, la temperatura sea positiva y el tiempo también.
         */
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<std::uint32_t> row;
            while (std::getline(iss, strValue, ';')) {
                aux = std::stoi(strValue);
                // NO se puede tener valores negativas
                if (aux < 0) {
                	throw std::exception();
                }
                row.emplace_back(aux);
            }
            if (row.size() != 3) {
            	throw std::exception();
            } else if (row[2] > 100) {
            	emit message("La potencia no puede superar 100%", ERROR);
            	return;
            }
            config.emplace_back(row);
        }
        /*
         * Se aplica un cambio de unidad a los tiempos, para pasarlo a
         * milisegundos
         */
        for (auto &row: config) {
            row[0] *= 1000;
        }
        this->controlDirectives = std::move(config);
        this->message("El archivo se cargó correctamente", OK);
    } catch (std::exception &e) {
        this->message("El csv está mal formateado", ERROR);
    }
}

void FromFileControlView::loadControlValues(std::string filepath) {
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
            this->ui->kpLineEdit->setText(QString(value.c_str()));
        } else if (key == "kd") {
            this->ui->kdLineEdit->setText(QString(value.c_str()));
        } else if (key == "ki") {
            this->ui->kiLineEdit->setText(QString(value.c_str()));
        } else {
            throw Exception("Invalid format of classic control parameters file");
        }
    }
}
