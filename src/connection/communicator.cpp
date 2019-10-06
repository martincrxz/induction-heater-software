//
// Created by Martín García on 24/08/2019.
//

#include <logger/logger.h>
#include "communicator.h"

Communicator::Communicator(QObject *parent): QObject(parent) {
    port = new SerialPort(this);
    while (!this->port->isConnected()) {
        port->findDevice();
    }
}

Communicator::~Communicator() {
    delete port;
}


/*void Communicator::run() {
    port = new SerialPort();
    while(keep_processing){
        if(!port->isConnected()) {
            port->findDevice();
        }
        QThread::sleep(5);
    }
}
*/
void Communicator::write(std::shared_ptr<MicroMessage> msg) {
    Logger::info("se llamó al write");
    this->port->send(msg);
}
