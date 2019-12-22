//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_CLASSIC_PID_H
#define TRABAJOPROFESIONAL_CLASSIC_PID_H


#include "algorithm.h"

class ClassicPID : public Algorithm{
private:
    float Kp = 0, Ki = 0, Kd = 0;
    
    float error = 0;
    float diffError = 0;
    float integralError = 0;

public:
	ClassicPID(float kp, float ki, float kd, float targetTemp);
	virtual ~ClassicPID() = default;
	virtual int process(std::shared_ptr<TemperatureReading> data) override;
};


#endif //TRABAJOPROFESIONAL_CLASSIC_PID_H
