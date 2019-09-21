//
// Created by Martín García on 18/09/2019.
//

#ifndef TRABAJOPROFESIONAL_SERIALPORT_H
#define TRABAJOPROFESIONAL_SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>

#define USB_READ_TIMEOUT 500 // ms
#define USB_WRITE_TIMEOUT 1 // ms

class SerialPort : public QSerialPort{
public:
    SerialPort();
    explicit SerialPort(QString);
    bool ping(QByteArray message_to_send, QByteArray message_to_receive);
};


#endif //TRABAJOPROFESIONAL_SERIALPORT_H
