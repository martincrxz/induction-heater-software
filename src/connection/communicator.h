//
// Created by Martín García on 24/08/2019.
//

#ifndef __COMMUNICATOR_H__
#define __COMMUNICATOR_H__

#include <iostream>

#include <QSerialPort>
#include <QSerialPortInfo>

#include "receiver.h"
#include "sender.h"

#define BAUDRATE 9600

class Communicator {

    private:
        Sender *sender;
        Receiver *receiver;
        QSerialPort *port;

    public:
        Communicator();
        ~Communicator();
        void findDevice();
};


#endif // __COMMUNICATOR_H__
