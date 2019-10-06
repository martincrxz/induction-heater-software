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

    this->connect(this, &SerialPort::deviceNotConnected, this, &SerialPort::findDevice);
    this->findDevice();
}

SerialPort::SerialPort() : QSerialPort() {
    this->setBaudRate(BAUDRATE);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
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
        Logger::info("Tratando de conectar a: " + info.portName().toStdString() + ".");
        this->setPort(info);
        this->open(QIODevice::ReadWrite);
        if( this->isOpen() ){
            std::shared_ptr<MicroMessage> ping(new PingMessage());
            this->send(ping);
            QByteArray response;
            if (this->receive(response)) {
                std::shared_ptr<MicroMessage> res(this->protocol.translate(
                        response));
                if (res->getId() == PONG_ID &&
                    ((PongMessage *) &(*res))->isConnected() ) {
                    Logger::info("Dispositivo conectado");
                    connected = true;
                } else {
                    Logger::info("la respuesta no fue exitosa");
                    this->close();
                }
            } else {
                Logger::info("se recibió basura");
                this->close();
            }
        } else {
            Logger::info("serial port no se pudo abrir");
            emit this->deviceNotConnected();
        }
    }
}

void SerialPort::send(std::shared_ptr<MicroMessage> msg) {
    QByteArray buff = protocol.translate(msg);
    this->write(buff);
    this->waitForBytesWritten(USB_WRITE_TIMEOUT);
}

SerialPort::~SerialPort() {
    this->close();
}
