//
// Created by Martín García on 18/09/2019.
//

#ifndef TRABAJOPROFESIONAL_SERIALPORT_H
#define TRABAJOPROFESIONAL_SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include "protocol/protocol.h"


#define BAUDRATE 115200
#define USB_READ_TIMEOUT 500 // ms
#define USB_WRITE_TIMEOUT 1 // ms
#define RECONNECTION_TIMEOUT 2000 // ms
#define PORT_SERIAL_NUMBER "12345679" // this is set up in firmware

class SerialPort : public QSerialPort{
    Q_OBJECT
private:
    bool connected = false;
    Protocol protocol;
    QTimer timer; // move to heap ?

public:
    explicit SerialPort(QObject *parent);
    ~SerialPort() override;
    void send(std::shared_ptr<MicroMessage> msg);
    std::shared_ptr<MicroMessage> receive();
    bool isConnected();

public slots:
    void findDevice();
    void handleError(QSerialPort::SerialPortError);
    void handleMessage();

signals:
    void shutdownAcknowledge(QString code, QString desc);
    void temperatureArrived(std::shared_ptr<MicroMessage> msg);

};


#endif //TRABAJOPROFESIONAL_SERIALPORT_H
