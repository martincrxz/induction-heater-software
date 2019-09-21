//
// Created by Martín García on 04/09/2019.
//

#include "receiver.h"

Receiver::~Receiver() {
    keep_processing = false;
    this->wait();
}

void Receiver::run(){
    while(keep_processing){
        if(port->waitForReadyRead(50)){
            QByteArray data = port->read(8);
            std::cout << data.toStdString();
        }
    }
}