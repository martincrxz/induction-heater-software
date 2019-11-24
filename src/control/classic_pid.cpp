//
// Created by Martín García on 11/11/2019.
//

#include <sstream>

#include "classic_pid.h"
#include "logger/logger.h"

ClassicPID::ClassicPID(float kp, float ki, float kd): Kp(kp), Ki(ki), Kd(kd) {
	std::ostringstream oss;
	oss << "ClassicPID constructor ( kp= ";
	oss << kp << ", kd= " << kd << ", ki= " << ki << ")";
	Logger::debug(oss.str());		
}

int ClassicPID::process(std::shared_ptr<TemperatureReading> temp) {
	std::ostringstream oss;
	oss << "procesanding: ";
	oss << temp->getData();
	Logger::info(oss.str());
    return 0;
}
