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
#define RECONNECTION_TIMEOUT 1000 // ms
#define PORT_SERIAL_NUMBER "12345679" // this is set up in firmware
#define PACKET_SIZE 0x08
#define ONE_BYTE 1

typedef enum {WAITING, READING} reading_status_t;

class SerialPort : public QSerialPort{
    Q_OBJECT
private:
    bool connected = false;
    Protocol protocol;
    QTimer reconectionTimer; // move to heap ?
    int arrivingBytesCount = 0;
    reading_status_t readingStatus = WAITING;
    QByteArray arrivingPacket;
    void processMessage(QByteArray);
    uint8_t crcChecksum(QByteArray, uint8_t);

public:
    explicit SerialPort(QObject *parent);
    ~SerialPort() override;
    void send(std::shared_ptr<MicroMessage> msg);

public slots:
    void findDevice();
    void handleError(QSerialPort::SerialPortError);
    void handleMessage();

signals:
    void shutdownAcknowledge(QString code, QString desc);
    void configurationAcknowledge(QString code, QString desc);
    void thermocoupleFault(QString code, QString desc);
    void temperatureArrived(std::shared_ptr<MicroMessage> msg);

};


#endif //TRABAJOPROFESIONAL_SERIALPORT_H
