//
// Created by Martín García on 11/11/2019.
//
#include <cmath>
#include <iostream>
#include <sstream>

#include "../connection/protocol/set_power.h"
#include "control_algorithm.h"
#include "logger/logger.h"

#define MINIMUM_TAP 0   // potencia maxima (100%)
#define MAXIMUM_TAP 127 // potencia minima (0%) 

ControlAlgorithm::ControlAlgorithm(float targetTemp, SerialPort *sp):
                        serialPort(sp),
                        targetTemp(targetTemp) {}

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
                Logger::info("Exiting control algorithm");
                keep_processing = false;
            } else {
                Logger::info("Recibido %0.2f °C", msg->getData());
            	std::uint8_t tapToSend = this->process(msg);
                Logger::info("Vueltas a enviar: %i", (int) tapToSend);
                std::shared_ptr<MicroMessage> msgPower(new SetPower(tapToSend));
                this->serialPort->send(msgPower);
            }
        }
    } catch(std::exception &e) {
        Logger::critical(e.what());
    } catch(...) {
        Logger::critical("Unknown error in ControlAlgorithm::run");
    }
}

void ControlAlgorithm::stop() {
	this->queue.push(nullptr);
}

ControlAlgorithm::~ControlAlgorithm() {
	Logger::debug("Destroying ControlAlgorithm");
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