//
// Created by Martín García on 24/08/2019.
//

#include "communicator.h"

Communicator::Communicator() {
    this->start();
}

Communicator::~Communicator() {
    this->keep_processing = false;
    this->wait();
}

void Communicator::run() {
    port = new SerialPort();
    while(keep_processing){
        if(!port->isConnected()) {
            port->findDevice();
        }
    }
}