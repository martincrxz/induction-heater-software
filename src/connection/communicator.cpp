//
// Created by Martín García on 24/08/2019.
//

#include "communicator.h"

Communicator::Communicator() {
    port = new QSerialPort();
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

void Communicator::findDevice() {
    auto portsInfo = QSerialPortInfo::availablePorts();
    for(const auto &info : portsInfo){
        QSerialPort temp(info.portName());
        temp.setBaudRate(BAUDRATE);
        temp.setDataBits(QSerialPort::Data8);
        temp.setParity(QSerialPort::NoParity);
        if(temp.open(QIODevice::ReadWrite)) {
            temp.flush();
            std::cout << "writing on " + temp.portName().toStdString() << std::endl;
            std::cout << temp.isWritable() << std::endl;
            QByteArray data(8,0);
            data[0] = 0x08;
            data[1] = 0x01;
            temp.write(data,8);
            temp.waitForBytesWritten(100);
            if(temp.waitForReadyRead(100)){
                QByteArray received = temp.readAll();
                if((char)received[0] == 0x08 && (char)received[1] == 0x02) {
                    port->setPort(info);
                    temp.close();
                    port->open(QIODevice::ReadWrite);
                    std::cout << "Device found" << std::endl;
                    return;
                }
            }
        }
        temp.close();
    }
}


