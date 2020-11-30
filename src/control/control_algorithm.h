//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_CONTROL_ALGORITHM_H
#define TRABAJOPROFESIONAL_CONTROL_ALGORITHM_H

#include <QtCore/QThread>
#include <memory>
#include <stream.h>
#include <mutex>

#include "../connection/protocol/temperature_reading.h"
#include "../connection/serialport.h"

#define WINDOW_SIZE 1

class ControlAlgorithm : public QThread{
    Q_OBJECT

private:
	IO::Stream<std::shared_ptr<TemperatureReading>> queue;
    SerialPort *serialPort;
    /**
     * @brief Lanza el hilo de ejecución que toma elementos de a uno y
     * los procesa de forma polimorfica (dependiendo de cada tipo de control)
     */
    void run() override;
public slots:

    void receiveData(TemperatureReading &data);

protected:
    std::atomic<bool> keep_processing{true};
    float targetTemp = 0;
    uint8_t window_size{WINDOW_SIZE};
    //  ventana de tiempo para procesar las muestras
    std::vector<float> errorValues;
    //  contador para pisar el ultimo valor en formato round robin
    uint64_t iteration = 0;
    std::mutex m;

public:
	ControlAlgorithm(float targetTemp, SerialPort *sp, uint8_t window_size);
	virtual ~ControlAlgorithm();
	/**
     * @brief Se encarga de terminar la ejecución ordenada
     * del hilo
     */
    void stop();
    virtual unsigned char process(std::shared_ptr<TemperatureReading> data) = 0;
    unsigned char _process(float temp);
    /**
     * @brief Convierte la potencia (numero real entre 0 y 100) a vueltas 
     * del potenciometro.
     * @param  power: real de 0 a 100 (si está fuera de este limite lo ajusta solo)
     * @return cantidad de vueltas para el potenciómetro   
     */
    static unsigned char powerToTaps(float power);
    static float tapsToPower(unsigned char taps);
    virtual void updateConfig();
};


#endif //TRABAJOPROFESIONAL_CONTROL_ALGORITHM_H
