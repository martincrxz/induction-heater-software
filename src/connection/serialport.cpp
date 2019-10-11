//
// Created by Martín García on 18/09/2019.
//

#include "serialport.h"
#include <iostream>
#include <logger/logger.h>

#define SEPARATOR ':'

SerialPort::SerialPort(QObject *parent) : QSerialPort(parent), timer(this) {
    this->setBaudRate(BAUDRATE);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);

    connect(&timer, &QTimer::timeout, this, &SerialPort::findDevice);
    connect(this, &SerialPort::errorOccurred, this, &SerialPort::handleError);
    connect(this, &SerialPort::readyRead, this, &SerialPort::handleMessage);
    this->findDevice();
}

SerialPort::~SerialPort() {
    if(this->isOpen())
        this->close();
}

void SerialPort::send(std::shared_ptr<MicroMessage> msg) {
    QByteArray buff = protocol.translate(msg);
    Logger::debug("Sending message: " + buff.toHex(SEPARATOR).
                  toStdString());
    this->write(buff);
    this->waitForBytesWritten(USB_WRITE_TIMEOUT);
}

std::shared_ptr<MicroMessage> SerialPort::receive() {
    if(this->waitForReadyRead(USB_READ_TIMEOUT)){
        QByteArray buff(8,0);
        buff = this->readLine(8);
        Logger::debug("Message received: " + buff.toHex(SEPARATOR).
                      toStdString());
        return protocol.translate(buff);
    }
    return nullptr;
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
                Logger::warning("Cannot open serial port.");
            }
        }
    }
    Logger::warning("Device not found.");
    timer.start(RECONNECTION_TIMEOUT);
}

void SerialPort::handleError(QSerialPort::SerialPortError error){
    Logger::warning("Serial port error - " + this->errorString().toStdString());
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

void SerialPort::handleMessage(){
    QByteArray buff = this->read(8);
    std::shared_ptr<MicroMessage> msg(this->protocol.translate(buff));
    switch(msg->getId()){
        case SHUTDOWN_ACK_ID:
            emit shutdownAcknowledge(QString::number(SHUTDOWN_ACK_ID),
                    "Se activo la parada de emergencia.");
            break;
        default:
            Logger::warning("Unknown message");
            break;
    }
}