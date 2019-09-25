//
// Created by Martín García on 18/09/2019.
//

#ifndef TRABAJOPROFESIONAL_SERIALPORT_H
#define TRABAJOPROFESIONAL_SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>

#define BAUDRATE 9600
#define USB_READ_TIMEOUT 500 // ms
#define USB_WRITE_TIMEOUT 1 // ms

class SerialPort : public QSerialPort{
public:
    SerialPort();
    void send(QByteArray &buff);
    bool receive(QByteArray &buff);
};


#endif //TRABAJOPROFESIONAL_SERIALPORT_H
