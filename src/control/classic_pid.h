//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_CLASSIC_PID_H
#define TRABAJOPROFESIONAL_CLASSIC_PID_H


#include "algorithm.h"

class ClassicPID : public Algorithm{
private:
    float Kp = 0, Ki = 0, Kd = 0;

public:
	ClassicPID(float kp, float ki, float kd);
	virtual ~ClassicPID() = default;
	int process(int data) override;
};


#endif //TRABAJOPROFESIONAL_CLASSIC_PID_H
