//
// Created by Martín García on 18/09/2019.
//

#include "serialport.h"
#include <iostream>
#include <logger/logger.h>
#include "protocol/ping_message.h"
#include "protocol/pong_message.h"

SerialPort::SerialPort(QObject *parent) : QSerialPort(parent), timer(this) {
    this->setBaudRate(BAUDRATE);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);

    connect(this, &SerialPort::deviceNotConnected, this, &SerialPort::findDevice);
    connect(&timer, &QTimer::timeout, this, &SerialPort::findDevice);
    connect(this, &SerialPort::errorOccurred, this, &SerialPort::handleError);
    this->findDevice();
}

SerialPort::~SerialPort() {
    this->close();
}

void SerialPort::send(std::shared_ptr<MicroMessage> msg) {
    Logger::info("Writing to device.");
    QByteArray buff = protocol.translate(msg);
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

bool SerialPort::isConnected() {
    return connected;
}

void SerialPort::findDevice() {
    auto portsInfo = QSerialPortInfo::availablePorts();
    for(auto &info : portsInfo){
        if(info.serialNumber() == PORT_SERIAL_NUMBER){
            this->setPort(info);
            if(this->open(QIODevice::ReadWrite)){
                timer.stop();
                Logger::info("Serial port connected.");
                connected = true;
                return;
            } else {
                Logger::info("Cannot open serial port.");
            }
        }
    }
    Logger::info("Device not found.");
    timer.start(RECONNECTION_TIMEOUT);
}

void SerialPort::handleError(QSerialPort::SerialPortError error){
    std::cout << "Serial port error: " << error << "." << std::endl;
    switch (error){
        case QSerialPort::ResourceError:
            this->close();
            this->connected = false;
            timer.start(RECONNECTION_TIMEOUT);
            break;
        default:
            break;
    }
}