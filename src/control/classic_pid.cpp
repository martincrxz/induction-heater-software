//
// Created by Martín García on 11/11/2019.
//

#include <sstream>

#include "classic_pid.h"
#include "logger/logger.h"

ClassicPID::ClassicPID(float kp, float ki, float kd): Kp(kp), Ki(ki), Kd(kd) {
		
}

int ClassicPID::process(int data) {
	std::ostringstream oss;
	oss << "procesanding: ";
	oss << data;
	Logger::info(oss.str());
    return 0;
}
