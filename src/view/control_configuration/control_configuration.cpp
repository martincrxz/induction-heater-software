#include "control_configuration.h"
#include "logger/logger.h"

#include "../../control/classic_pid.h"
ControlConfiguration::ControlConfiguration(QWidget *parent, SerialPort *sp, QDoubleValidator *tv) :
        QWidget(parent),
        sp(sp),
        tempValidator(tv)
{

}

ControlConfiguration::~ControlConfiguration() {
    Logger::debug("Destroying ControlConfiguration");
}

void ControlConfiguration::start(float targetTemp)
{
    Logger::info("Initiating control algorithm");
    if (this->controlAlgorithm == nullptr) {
//        this->controlAlgorithm.reset(new ClassicPID(1,2,3));
        this->instantiate(targetTemp);
        emit message("Se activó el proceso de control correctamente", OK);
    } else {
        emit message("Hay un proceso activo.", ERROR);
    }
}

void ControlConfiguration::stop() {
    Logger::info("Stopping control algorithm");
    if (this->controlAlgorithm != nullptr) {
        this->controlAlgorithm.reset(nullptr);
        emit message("Proceso detenido correctamente", OK);
    } else {
        emit message("No hay proceso que desactivar", ERROR);
    }
}
void ControlConfiguration::dataAvailable(TemperatureReading &temp) {
    if (this->controlAlgorithm != nullptr) {
        this->controlAlgorithm->receiveData(temp);
    }
}
