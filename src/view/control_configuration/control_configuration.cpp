#include <fstream>
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

void ControlConfiguration::saveConstantsInFile(float kp, float ki, float kd, std::string filename) {

    std::fstream file(filename, std::fstream::out |
                                std::fstream::trunc);
    file << "kp " << kp << std::endl;
    file << "ki " << ki << std::endl;
    file << "kd " << kd << std::endl;

    Logger::info("Data saved in file: %s", filename.c_str());

}

void ControlConfiguration::updateConfig(const AppConfig &conf) {
    this->window_size = conf.window_size;
    if (this->controlAlgorithm) {
        Logger::debug("Control %s updated", this->getName());
        this->controlAlgorithm->updateConfig(conf);
    }
}