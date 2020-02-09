//
// Created by Martín García on 11/11/2019.
//

#include <sstream>
#include <numeric>

#include "classic_pid.h"
#include "logger/logger.h"

//  TODO: se podría hacer configurable en runtime
#define WINDOW_SIZE 4

ClassicPID::ClassicPID(float kp, float ki, float kd, float targetTemp, SerialPort *sp):
        ControlAlgorithm(targetTemp, sp), Kp(kp), Ki(ki), Kd(kd),
        errorValues() {
	Logger::debug("ClassicPID constructor ( kp= %.2f, kd= %.2f, ki= %.2f). Target temperature: %.0f °C",
		kp, kd, ki, targetTemp);		
}

unsigned char ClassicPID::process(std::shared_ptr<TemperatureReading> temp) {
	/**
	 *	El control se va a aplicar usando una ventana de tiempo, donde se 
	 *	calcula el error medio de esa ventana.
	 *
	 *	A nivel código, esto significa que el programa agregará elementos al
	 *	vector hasta que el tamaño de este sea el de la ventana. Cuando esto
	 *	suceda, cada temperatura nueva reemplazará a la temperatura mas antigua,
	 *	en formato round-robin.
	 */
	if (errorValues.size() < WINDOW_SIZE) 
		errorValues.emplace_back(this->targetTemp - temp->getData());
	else
		this->errorValues[iteration % WINDOW_SIZE] = this->targetTemp - temp->getData();
	iteration++;

	float errorMean = std::accumulate(this->errorValues.begin(), 
								this->errorValues.end(), 0);
	errorMean /= this->errorValues.size();
	
	derivativeError = errorMean - previousErrorMean; 
	previousErrorMean = errorMean;
	integralError += errorMean;
	/**
	 *	Segun la implementación vieja, el control PID devuelve las vueltas
	 *	que se le debe aplicar al potenciometro (debería ser potencia). 
	 */
	float power = (Kp * errorMean + Kd * derivativeError + Ki * integralError);
	return ControlAlgorithm::powerToTaps(power);	
}
