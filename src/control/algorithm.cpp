//
// Created by Martín García on 11/11/2019.
//
#include <iostream>
#include <sstream>

#include "algorithm.h"
#include "logger/logger.h"

Algorithm::Algorithm(float targetTemp): targetTemp(targetTemp) {}

void Algorithm::receiveData(TemperatureReading &data) {
    std::shared_ptr<TemperatureReading> temp(new TemperatureReading(data));
	this->queue.push(temp);
}

void Algorithm::run() {
	 try {
        while (keep_processing) {
            std::shared_ptr<TemperatureReading> msg;
            // pop bloqueante
            queue.pop(msg, true);
            if (msg == nullptr) {
                Logger::info("Exiting control algorithm");
                keep_processing = false;
            } else {
                std::ostringstream oss;
                oss << "Recibido " << msg->getData() << " °C";
                Logger::info(oss.str());
            	int tapToSend = this->process(msg);
                oss = std::ostringstream();
                oss << "Vueltas a enviar: ";
                oss << tapToSend;
                Logger::info(oss.str());
            }
        }
    } catch(std::exception &e) {
        Logger::critical(e.what());
    } catch(...) {
        Logger::critical("Unknown error in Algorithm::run");
    }
}

void Algorithm::stop() {
	this->queue.push(nullptr);
}

Algorithm::~Algorithm() {
	Logger::debug("Destroying Algorithm");
    this->stop();
    this->wait();
}
