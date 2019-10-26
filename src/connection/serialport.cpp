//
// Created by Martín García on 18/09/2019.
//

#include "serialport.h"
#include <iostream>
#include <sstream>
#include <logger/logger.h>

#define SEPARATOR ':'

SerialPort::SerialPort(QObject *parent) :
QSerialPort(parent),
timer(this),
packet(8,0)
{
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
                this->clear();
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
    std::ostringstream oss("Serial port error - ");
    oss << this->errorString().toStdString() << " (";
    oss << (int) error << ")";
    Logger::warning(oss.str());
    // TODO: tal vez debería intentar reconectarse siempre.
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
    qint64 bytesAvailabe = this->bytesAvailable();
    for(int i = 0; i < bytesAvailabe; i++){
        QByteArray byteRead = this->read(1);
        switch(readingStatus){
            case WAITING:
                if(byteRead[0].operator==(0x7E)){
                    packet[count] = byteRead[0];
                    count++;
                    readingStatus = READING;
                }
                break;
            case READING:
                packet[count] = byteRead[0];
                count++;
                if(count == PACKET_SIZE){
                    readingStatus = WAITING;
                    count = 0;
                    processMessage(packet);
                }
                break;
        }
    }
}

void SerialPort::processMessage(QByteArray buff){
    std::cout << this->bytesAvailable() << std::endl;
    if(crcChecksum(buff, PACKET_SIZE-1)==buff[PACKET_SIZE-1]) {
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
                Logger::info("Cold junction message.");
                break;
            case THERMOCOUPLE_FAULT:
                Logger::info("Thermocouple fault message");
                break;
            case THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE:
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
                toStdString());
    }
}

uint8_t SerialPort::crcChecksum(QByteArray data, uint8_t size){
    int16_t i;
    uint8_t chk = 0xFF;

    for (i=0; i < size; i++)
        chk -= data[i];

    return chk;
}