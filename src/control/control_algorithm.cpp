//
// Created by Martín García on 11/11/2019.
//
#include <cmath>
#include <iostream>
#include <messages.h>
#include <sstream>

#include "../connection/protocol/set_power.h"
#include "control_algorithm.h"
#include "logger/logger.h"
#include "../configuration/app_config.h"

#define MINIMUM_TAP 0   // potencia maxima (100%)
#define MAXIMUM_TAP 127 // potencia minima (0%) 

ControlAlgorithm::ControlAlgorithm(float targetTemp, SerialPort *sp, uint8_t window_size):
                        serialPort(sp),
                        targetTemp(targetTemp),
                        window_size(window_size) {}

void ControlAlgorithm::receiveData(TemperatureReading &data) {
    std::shared_ptr<TemperatureReading> temp(new TemperatureReading(data));
	this->queue.push(temp);
}

void ControlAlgorithm::run() {
	 try {
        while (keep_processing) {
            std::shared_ptr<TemperatureReading> msg;
            // pop bloqueante
            queue.pop(msg, true);
            if (msg == nullptr) {
                Logger::info(CONTROL_ALGORITHM_EXIT_MSG);
                keep_processing = false;
            } else {
                Logger::info(CONTROL_ALGORITHM_TEMP_RECEIVED_MSG, msg->getData());
            	std::uint8_t tapToSend = this->process(msg);
                Logger::info(CONTORL_ALGORITHM_OUTPUT_MSG, (int) tapToSend);
                std::shared_ptr<MicroMessage> msgPower(new SetPower(tapToSend));
                this->serialPort->send(msgPower);
            }
        }
    } catch(std::exception &e) {
        Logger::critical(e.what());
    } catch(...) {
        Logger::critical(UNKNOWN_ERROR_MSG, "control_algorithm");
    }
}

void ControlAlgorithm::stop() {
	this->queue.push(nullptr);
}

ControlAlgorithm::~ControlAlgorithm() {
	Logger::debug(CONTROL_ALGORITHM_DESTROY_MSG);
    this->stop();
    this->wait();
}

unsigned char ControlAlgorithm::powerToTaps(float power) {
    //  Si el calculo de la potencia supera los limites permitidos, se corrige
    if (power > 100) 
        power = 100;
    if (power < 10)
        power = 10;
    //  Se devuelve las vueltas del potenciometro (es muy feo esto, esta 
    //  transformacion debería hacerla el código del micro).
    float taps = (100 - power) * MAXIMUM_TAP / 100;
    return (unsigned char) std::floor(taps);
}

void ControlAlgorithm::updateConfig() {
    std::lock_guard<std::mutex> lock(this->m);
    this->window_size = ApplicationConfig::instance().getWindowSize();
    this->errorValues.clear();
    iteration = 0;
}
