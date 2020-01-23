//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_CONTROL_ALGORITHM_H
#define TRABAJOPROFESIONAL_CONTROL_ALGORITHM_H

#include <QtCore/QThread>
#include <memory>
#include <stream.h>

#include "../connection/protocol/temperature_reading.h"
#include "../connection/serialport.h"

class ControlAlgorithm : public QThread{
    Q_OBJECT

private:
	IO::Stream<std::shared_ptr<TemperatureReading>> queue;
    bool keep_processing{true};
    SerialPort *serialPort;
    /**
     * @brief Lanza el hilo de ejecución que toma elementos de a uno y
     * los procesa de forma polimorfica (dependiendo de cada tipo de control)
     */
    void run() override;
    virtual unsigned char process(std::shared_ptr<TemperatureReading> data) = 0;

public slots:
	void receiveData(TemperatureReading &data);

protected:
    float targetTemp = 0;

public:
	ControlAlgorithm(float targetTemp, SerialPort *sp);
	virtual ~ControlAlgorithm();
	/**
     * @brief Se encarga de terminar la ejecución ordenada
     * del hilo
     */
    void stop();
    /**
     * @brief Convierte la potencia (numero real entre 0 y 100) a vueltas 
     * del potenciometro.
     * @param  power: real de 0 a 100 (si está fuera de este limite lo ajusta solo)
     * @return cantidad de vueltas para el potenciómetro   
     */
    static unsigned char powerToTaps(float power);
};


#endif //TRABAJOPROFESIONAL_CONTROL_ALGORITHM_H
