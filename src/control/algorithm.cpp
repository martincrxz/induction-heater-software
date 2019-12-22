//
// Created by Martín García on 11/11/2019.
//
#include <iostream>

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
            queue.pop(msg, true);
            if (msg == nullptr) {
                Logger::info("Exiting control algorithm");
                keep_processing = false;
            } else {
            	this->process(msg);
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
