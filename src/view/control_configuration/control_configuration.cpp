#include "control_configuration.h"
#include "logger/logger.h"


ControlConfiguration::ControlConfiguration(QWidget *parent, SerialPort *sp) :
        QWidget(parent),
        sp(sp)
{

}

ControlConfiguration::~ControlConfiguration() {
    Logger::debug("Destroying ControlConfiguration");
}

void ControlConfiguration::start()
{
    Logger::info("Initiating control algorithm");
    if (this->controlAlgorithm == nullptr) {
        this->instantiate();
    }
}

void ControlConfiguration::stop() {
    Logger::info("Stopping control algorithm");
    this->controlAlgorithm.reset(nullptr);
}
void ControlConfiguration::dataAvailable(TemperatureReading &temp) {
    if (this->controlAlgorithm != nullptr) {
        this->controlAlgorithm->receiveData(temp);
    }
}
