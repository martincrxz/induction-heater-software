//
// Created by Martín García on 18/09/2019.
//

#include "serialport.h"
#include <iostream>

SerialPort::SerialPort() : QSerialPort() {}

SerialPort::SerialPort(QString name) : QSerialPort(name) {}

bool SerialPort::ping(QByteArray message_to_send, QByteArray message_to_receive) {
    this->flush();
    this->write(message_to_send);
    this->waitForBytesWritten(USB_WRITE_TIMEOUT);
    if(this->waitForReadyRead(USB_READ_TIMEOUT)){
        QByteArray message_received = this->readAll();
        std::cout << (int)message_received[1] << std::endl;
        std::cout << (int)message_to_receive[1] << std::endl;
        if(message_received[1] == message_to_receive[1])
            return true;
    }
    return false;
}