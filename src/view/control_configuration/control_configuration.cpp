#include <fstream>
#include "messages.h"

#include "control_configuration.h"
#include "configuration/app_config.h"
#include "logger/logger.h"


ControlConfiguration::ControlConfiguration(QWidget *parent, SerialPort *sp) :
        QWidget(parent),
        sp(sp) {}

ControlConfiguration::~ControlConfiguration() {
    Logger::debug(CONTORL_CONFIGURATION_DESTRUCTOR_MSG);
}

void ControlConfiguration::start()
{
    Logger::info(CONTORL_CONFIGURATION_INIT_MSG);
    if (this->controlAlgorithm == nullptr) {
        this->instantiate();
    }
}

void ControlConfiguration::stop() {
    Logger::info(CONTROL_CONFIGURATION_STOP_MSG);
    this->controlAlgorithm.reset(nullptr);
}
void ControlConfiguration::dataAvailable(TemperatureReading &temp) {
    if (this->controlAlgorithm != nullptr) {
        this->controlAlgorithm->receiveData(temp);
    }
}

void ControlConfiguration::updateConfig() {
    this->window_size = ApplicationConfig::instance().getWindowSize();
    if (this->controlAlgorithm) {
        Logger::debug(CONTORL_CONFIGURATION_VARIABLE_UPDATED_MSG, this->getName(),
                        this->window_size);
        this->controlAlgorithm->updateConfig();
    }
}