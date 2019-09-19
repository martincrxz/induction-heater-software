//
// Created by Martín García on 24/08/2019.
//

#include "communicator.h"

Communicator::Communicator() {
    port = new SerialPort();
    findDevice();
    receiver = new Receiver(*port);
    sender = new Sender(*port);
    receiver->start();
    sender->start();
}

Communicator::~Communicator(){
    delete sender;
    delete receiver;
    port->close();
    delete port;
}

bool Communicator::findDevice() {
    auto portsInfo = QSerialPortInfo::availablePorts();
    QByteArray message_to_send(8,0);
    message_to_send[0] = 0x08;
    message_to_send[1] = 0x01;
    QByteArray message_to_receive(8,0);
    message_to_receive[0] = 0x08;
    message_to_receive[1] = 0x02;
    for(const auto &info : portsInfo){
        std::cout << info.portName().toStdString() << std::endl;
        SerialPort temp(info.portName());
        temp.setBaudRate(BAUDRATE);
        temp.setDataBits(QSerialPort::Data8);
        temp.setParity(QSerialPort::NoParity);
        if(temp.open(QIODevice::ReadWrite)) {
            if(temp.ping(message_to_send, message_to_receive)) {
                temp.close();
                port->setPort(info);
                std::cout << "Device found." << std::endl;
                return true;
            }
            else
                temp.close();
        }
    }
    return false;
}


