//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_CLASSIC_PID_H
#define TRABAJOPROFESIONAL_CLASSIC_PID_H


#include "control_algorithm.h"
#include <cstdint>
#include <mutex>

class ClassicPID : public ControlAlgorithm {
protected:
    float Kp = 0, Ki = 0, Kd = 0;
    float errorMean = 0;
    float previousErrorMean = 0;
    float derivativeError = 0;
    float integralError = 0;

public:
	ClassicPID(float kp, float ki, float kd, float targetTemp, SerialPort *sp, uint8_t window_size);
	virtual ~ClassicPID() = default;
	/**
	 *	Dado una temperatura nueva, calcula por medio del control clásico
	 *	la potencia que debe aplicar el horno. El valor de retorno es la
	 *	cantidad de vueltas que debe dar el potenciómetro electrónico.
	 *
	 *	TODO: está conceptualmente mal que devuelva la cantidad de vueltas.
	 *	La aplicación no debe saber como el horno controla la potencia a 
	 *	aplicar. Esta transformación debe hacerla el micro.
	 */
	virtual unsigned char process(std::shared_ptr<TemperatureReading> data) override;
};


#endif //TRABAJOPROFESIONAL_CLASSIC_PID_H
