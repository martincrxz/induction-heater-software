//
// Created by Martín García on 24/08/2019.
//

#ifndef __COMMUNICATOR_H__
#define __COMMUNICATOR_H__

#include <iostream>
#include <QThread>

#include "protocol/protocol.h"
#include "serialport.h"

#define SENDING_PING_TYPE 0xaa
#define RECEIVING_PING_TYPE 0x0a

class Communicator : QThread{
    Q_OBJECT
private:
    SerialPort *port = nullptr;
    bool keep_processing = true;

public:
    explicit Communicator();
    void run() override;
    ~Communicator() override;
};


#endif // __COMMUNICATOR_H__
