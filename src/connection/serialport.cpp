//
// Created by Martín García on 18/09/2019.
//

#include "serialport.h"
#include "protocol/thermocouple_fault.h"
#include "messages.h"
#include "ui_general_view.h"

#include <iostream>
#include <sstream>
#include <logger/logger.h>
#include <vector>

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
}

SerialPort::~SerialPort() {
    if(this->isOpen())
        this->close();
}

void SerialPort::send(std::shared_ptr<MicroMessage> msg) {
    QByteArray buff = protocol.translate(msg);
    Logger::debug(SERIALPORT_SENDING_MSG, buff.toHex(SEPARATOR).
            toStdString().c_str());
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
                emit serialPortConnected();
                Logger::info(SERIALPORT_CONNECTED_MSG);
                connected = true;
                this->clear();
                return;
            } else {
                Logger::warning(SERIALPORT_CONNECT_FAILED_MSG);
            }
        }
    }
    Logger::warning(SERIAL_PORT_DEVICE_NOT_FOUND_MSG);
    reconectionTimer.start(RECONNECTION_TIMEOUT);
}

void SerialPort::handleError(QSerialPort::SerialPortError error){
    Logger::warning(SERIAL_PORT_HANDLE_ERROR_MSG, 
        this->errorString().toStdString().c_str(),
        (int) error);
    // TODO: tal vez debería intentar reconectarse siempre.
    if (this->isOpen()){
        this->close();
        this->connected = false;
    }
    emit serialPortDisconnected();
    reconectionTimer.start(RECONNECTION_TIMEOUT);
}

void SerialPort::handleMessage(){
    QByteArray readArray = this->readAll();
    for(auto readByte : readArray){
        switch(readingStatus){
            case WAITING:
                if(readByte == 0x7E){
                    arrivingPacket[arrivingBytesCount] = readByte;
                    arrivingBytesCount++;
                    readingStatus = READING;
                }
                break;
            case READING:
                arrivingPacket[arrivingBytesCount] = readByte;
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
        Logger::debug(SERIALPORT_RECEIVED_MSG, buff.toHex(SEPARATOR).
                toStdString().c_str());
        std::shared_ptr<MicroMessage> msg(this->protocol.translate(buff));
        switch(msg->getId()) {
            case SHUTDOWN_ACKNOWLEDGE:
                emit shutdownAcknowledge(QString::number(SHUTDOWN_ACKNOWLEDGE),
                        SERIALPORT_EMERGENCY_STOP_ACTIVATED_MSG);
                break;
            case TEMPERATURE_READING:
                emit temperatureArrived(msg);
                break;
            case COLD_JUNCTION_READING:
                emit coldJunctionArrived(msg);
                break;
            case THERMOCOUPLE_FAULT: {
                std::vector<QString> errors = ((ThermocoupleFault&)(*msg)).error();
                for (QString &msg: errors) {
                    emit thermocoupleFault(QString::number(THERMOCOUPLE_FAULT), msg);
                    Logger::info(SERIALPORT_THERMOCOUPLE_ERROR_RECEIVED_MSG, msg.toStdString().c_str());                    
                }
                break;
            } case THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE:
                emit configurationAcknowledge(QString::number(THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE),
                        SERIALPORT_THERMOCOUPLE_CONFIG_ACK + buff.toHex(SEPARATOR));
                Logger::info(SERIALPORT_THERMOCOUPLE_CONFIG_ACK);
                break;
            case POWER_SET_ACKNOWLEDGE:
                emit powerSetAcknowledge(msg);
                Logger::info(SERIALPORT_POWER_SET_ACK_MSG);
                break;
            case MANUAL_CONTROL_ACKNOWLEDGE:
                emit manualControlAcknowledge();
                emit manualControlAcknowledge(QString::number(MANUAL_CONTROL_ACKNOWLEDGE),
                                              SERIALPORT_MANUAL_CONTROL_SET_ACK_MSG);
                Logger::info(SERIALPORT_MANUAL_CONTROL_SET_ACK_MSG);
                break;
            case AUTOMATIC_CONTROL_ACKNOWLEDGE:
                emit automaticControlAcknowledge();
                emit automaticControlAcknowledge(QString::number(AUTOMATIC_CONTROL_ACKNOWLEDGE),
                                                 SERIALPORT_AUTOMATIC_CONTROL_SET_ACK_MSG);
                Logger::info(SERIALPORT_AUTOMATIC_CONTROL_SET_ACK_MSG);
                break;
            case CURRENT_FREQUENCY_READING:
                emit currentFrequencyArrived(msg);
                break;
            case CURRENT_RMS_READING:
                emit currentRMSArrived(msg);
                break;
            default:
                Logger::warning(SERIALPORT_UNKOWN_MSG);
                break;
        }
    }
    else {
        Logger::warning(SERIALPORT_CRC_FAILED_MSG,
            buff.toHex(SEPARATOR).toStdString().c_str(), 
            buff[7],
            crc);
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
