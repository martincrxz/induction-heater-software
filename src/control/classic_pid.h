//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_CLASSIC_PID_H
#define TRABAJOPROFESIONAL_CLASSIC_PID_H


#include "algorithm.h"
#include <cstdint>

class ClassicPID : public Algorithm{
private:
    float Kp = 0, Ki = 0, Kd = 0;
    //	ventana de tiempo para procesar las muestras
    std::vector<float> errorValues;
    float previousErrorMean = 0;
  	float derivativeError = 0;
    float integralError = 0;
    //	contador para pisar el ultimo valor en formato round robin
    uint64_t iteration = 0;

public:
	ClassicPID(float kp, float ki, float kd, float targetTemp);
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
	virtual int process(std::shared_ptr<TemperatureReading> data) override;
};


#endif //TRABAJOPROFESIONAL_CLASSIC_PID_H
