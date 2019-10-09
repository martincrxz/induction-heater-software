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
#define PORT_SERIAL_NUMBER "12345679"

class SerialPort : public QSerialPort{
    Q_OBJECT
private:
    bool connected = false;
    Protocol protocol;

public:
    explicit SerialPort(QObject *parent);
    ~SerialPort();
    void send(std::shared_ptr<MicroMessage> msg);
    bool receive(QByteArray &buff);
    bool isConnected();

public slots:
    void findDevice();

signals:
    void deviceNotConnected();

};


#endif //TRABAJOPROFESIONAL_SERIALPORT_H
