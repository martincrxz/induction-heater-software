//
// Created by Martín García on 24/08/2019.
//

#ifndef __COMMUNICATOR_H__
#define __COMMUNICATOR_H__

#include <iostream>

#include "protocol/protocol.h"
#include "serialport.h"
#include "receiver.h"
#include "sender.h"

#define SENDING_PING_TYPE 0xaa
#define RECEIVING_PING_TYPE 0x0a

class Communicator {

private:
    SerialPort port;
    Protocol protocol;
    Receiver receiver;
    Sender sender;

public:
    Communicator();
    ~Communicator();
};


#endif // __COMMUNICATOR_H__
