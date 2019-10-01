//
// Created by Martín García on 18/09/2019.
//

#include "serialport.h"
#include <iostream>
#include <logger/logger.h>
#include "protocol/ping_message.h"
#include "protocol/pong_message.h"

SerialPort::SerialPort(QObject *parent) : QSerialPort(parent) {
    this->setBaudRate(BAUDRATE);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
}

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

bool SerialPort::isConnected() {
    return connected;
}

void SerialPort::findDevice() {
    auto portsInfo = QSerialPortInfo::availablePorts();
    for(auto &info : portsInfo){
        this->setPort(info);
        if(this->open(QIODevice::ReadWrite)){
            Logger::info("Tratando de conectar a: " + info.portName().toStdString() + ".");
            PingMessage ping;
            QByteArray msg_to_send = protocol.translate(&ping);
            send(msg_to_send);
            QByteArray response;
            if (this->receive(response)) {
                std::shared_ptr<MicroMessage> res(this->protocol.translate(
                        response));
                if (res->getId() == PONG_ID &&
                    ((PongMessage *) &(*res))->isConnected() ) {
                    Logger::info("Dispositivo conectado");
                    connected = true;
                } else {
                    this->close();
                }
            } else {
                this->close();
            }
        }
    }
}
