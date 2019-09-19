//
// Created by Martín García on 24/08/2019.
//

#ifndef __COMMUNICATOR_H__
#define __COMMUNICATOR_H__

#include <iostream>

#include "serialport.h"
#include "receiver.h"
#include "sender.h"

#define SENDING_PING_TYPE 0xaa
#define RECEIVING_PING_TYPE 0x0a
#define BAUDRATE 9600

class Communicator {

    private:
        Sender *sender;
        Receiver *receiver;
        SerialPort *port;

    public:
        Communicator();
        ~Communicator();
        bool findDevice();
};


#endif // __COMMUNICATOR_H__
