//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_ALGORITHM_H
#define TRABAJOPROFESIONAL_ALGORITHM_H

#include <QtCore/QThread>
#include <memory>
#include <stream.h>

#include "../connection/protocol/temperature_reading.h"
#include "../connection/serialport.h"

class Algorithm : public QThread{
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
	Algorithm(float targetTemp, SerialPort *sp);
	virtual ~Algorithm();
	/**
     * @brief Se encarga de terminar la ejecución ordenada
     * del hilo
     */
    void stop();
};


#endif //TRABAJOPROFESIONAL_ALGORITHM_H
