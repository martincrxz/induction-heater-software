//
// Created by Martín García on 18/09/2019.
//

#include "serialport.h"
#include <iostream>

SerialPort::SerialPort() : QSerialPort() {
    this->setBaudRate(BAUDRATE);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
}

void SerialPort::send(QByteArray &buff) {
    this->write(buff);
    this->waitForBytesWritten(USB_WRITE_TIMEOUT);
}

bool SerialPort::receive(QByteArray &buff) {
    if(this->waitForReadyRead(USB_READ_TIMEOUT)){
        buff = this->readLine(8);
        return true;
    }
    return false;
}
