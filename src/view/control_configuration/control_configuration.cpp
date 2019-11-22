#include "control_configuration.h"
#include "logger/logger.h"

#include "src/control/classic_pid.h"
ControlConfiguration::ControlConfiguration(QWidget *parent) : QWidget(parent)
{

}

void ControlConfiguration::start()
{
    Logger::info("Initiating control algorithm");
    if (this->controlAlgorithm == nullptr) {
        this->controlAlgorithm.reset(new ClassicPID(1,2,3));
        //this->instantiate();
    } else {
        emit message("Hay un proceso activo.", ERROR);
    }
}

void ControlConfiguration::stop() {
    Logger::info("Stopping control algorithm");
    if (this->controlAlgorithm != nullptr) {
        this->controlAlgorithm->stop();
        this->controlAlgorithm->wait();
        this->controlAlgorithm.release();
    } else {
        emit message("No hay proceso que desactivar", ERROR);
    }
}
