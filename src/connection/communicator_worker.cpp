//
// Created by Martín García on 04/09/2019.
//

#include "communicator_worker.h"

CommunicatorWorker::CommunicatorWorker(){
    port = new QSerialPort("cu.usbmodem0E21F7F11");
    port->setBaudRate(9600);
    port->open(QIODevice::ReadWrite);
    if(!port->isOpen())
        throw Exception("Cannot open serial port.");
    else
        std::cout << "Serial port opened." << std::endl;
}

CommunicatorWorker::~CommunicatorWorker() {
    this->keep_processing = false;
    port->close();
    this->wait();
    delete port;
}

void CommunicatorWorker::run() {
    while(keep_processing){
        if(port->waitForReadyRead(50)){
            QByteArray data = port->read(8);
            std::cout << data.toStdString();
        }
    }
}
