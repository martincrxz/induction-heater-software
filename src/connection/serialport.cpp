//
// Created by Martín García on 18/09/2019.
//

#include "serialport.h"
#include "protocol/thermocouple_fault.h"
#include <iostream>
#include <sstream>
#include <logger/logger.h>

#define SEPARATOR ':'

SerialPort::SerialPort(QObject *parent) :
QSerialPort(parent),
reconectionTimer(this),
arrivingPacket(8,0)
{
    this->setBaudRate(BAUDRATE);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);

    connect(&reconectionTimer, &QTimer::timeout, this, &SerialPort::findDevice);
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

void SerialPort::findDevice() {
    auto portsInfo = QSerialPortInfo::availablePorts();
    for(auto &info : portsInfo){
        if(info.serialNumber() == PORT_SERIAL_NUMBER){
            this->setPort(info);
            if(this->open(QIODevice::ReadWrite)){
                reconectionTimer.stop();
                Logger::info("Serial port connected.");
                connected = true;
                this->clear();
                return;
            } else {
                Logger::warning("Cannot open serial port.");
            }
        }
    }
    Logger::warning("Device not found.");
    reconectionTimer.start(RECONNECTION_TIMEOUT);
}

void SerialPort::handleError(QSerialPort::SerialPortError error){
    std::ostringstream oss;
    oss << "Serial port error - ";
    oss << this->errorString().toStdString() << " (";
    oss << (int) error << ")";
    Logger::warning(oss.str());
    // TODO: tal vez debería intentar reconectarse siempre.
    if (this->isOpen()){
        this->close();
        this->connected = false;
    }
    reconectionTimer.start(RECONNECTION_TIMEOUT);
}

void SerialPort::handleMessage(){
    qint64 bytesAvailable = this->bytesAvailable();
    for(int i = 0; i < bytesAvailable; i++){
        QByteRef byteRead = this->read(ONE_BYTE)[0];
        switch(readingStatus){
            case WAITING:
                if(byteRead.operator==(0x7E)){
                    arrivingPacket[arrivingBytesCount] = byteRead;
                    arrivingBytesCount++;
                    readingStatus = READING;
                }
                break;
            case READING:
                arrivingPacket[arrivingBytesCount] = byteRead;
                arrivingBytesCount++;
                if(arrivingBytesCount == PACKET_SIZE){
                    readingStatus = WAITING;
                    arrivingBytesCount = 0;
                    processMessage(arrivingPacket);
                }
                break;
        }
    }
}

void SerialPort::processMessage(QByteArray buff){
    int crc = crcChecksum(buff, PACKET_SIZE-1);
    if(crc==(uint8_t)buff[PACKET_SIZE-1]) {
        Logger::debug("Message received: " + buff.toHex(SEPARATOR).
                toStdString());
        std::shared_ptr<MicroMessage> msg(this->protocol.translate(buff));
        switch(msg->getId()) {
            case SHUTDOWN_ACKNOWLEDGE:
                emit shutdownAcknowledge(QString::number(SHUTDOWN_ACKNOWLEDGE),
                        "Se activo la parada de emergencia.");
                break;
            case TEMPERATURE_READING:
                emit temperatureArrived(msg);
                break;
            case COLD_JUNCTION_READING:
                emit coldJunctionArrived(msg);
                break;
            case THERMOCOUPLE_FAULT:
                emit thermocoupleFault(QString::number(THERMOCOUPLE_FAULT),
                        ((ThermocoupleFault&)(*msg)).error());
                Logger::info("Thermocouple fault message");
                break;
            case THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE:
                emit configurationAcknowledge(QString::number(THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE),
                        "Config. ACK: " + buff.toHex(SEPARATOR));
                Logger::info("Thermocouple configuration acknowledge message.");
                break;
            case POWER_SET_ACKNOWLEDGE:
                Logger::info("Power set acknowledge message.");
                break;
            case MANUAL_CONTROL_ACKNOWLEDGE:
                Logger::info("Manual control activated message.");
                break;
            case AUTOMATIC_CONTROL_ACKNOWLEDGE:
                Logger::info("Automatic control activated message.");
                break;
            default:
                Logger::warning("Unknown message");
                break;
        }
    }
    else {
        Logger::warning("CRC failed: " + buff.toHex(SEPARATOR).
                toStdString() + " | " + std::to_string(buff[7]) + " : " + std::to_string(crc));
    }
}

uint8_t SerialPort::crcChecksum(QByteArray data, uint8_t size){
    int16_t i;
    uint16_t chk = 0xFF;

    for (i=0; i < size; i++)
        chk -= data[i];

    chk &= 0xff;

    return (uint8_t)chk;
}