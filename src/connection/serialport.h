//
// Created by Martín García on 18/09/2019.
//

#ifndef TRABAJOPROFESIONAL_SERIALPORT_H
#define TRABAJOPROFESIONAL_SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include "protocol/protocol.h"


#define BAUDRATE 9600
#define USB_READ_TIMEOUT 500 // ms
#define USB_WRITE_TIMEOUT 1 // ms

class SerialPort : public QSerialPort{
private:
    bool connected = false;
    Protocol protocol;

public:
    SerialPort();
    explicit SerialPort(QObject *parent);
    void send(std::shared_ptr<MicroMessage> msg);
    bool receive(QByteArray &buff);
    bool isConnected();
    void findDevice();
};


#endif //TRABAJOPROFESIONAL_SERIALPORT_H
