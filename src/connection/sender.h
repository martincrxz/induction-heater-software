//
// Created by Martín García on 04/09/2019.
//

#ifndef __SENDER_H__
#define __SENDER_H__

#include <iostream>
#include <QThread>
#include <QSerialPort>

#include "serialport.h"
#include "protocol/protocol.h"
#include "receiver.h"

class Sender : public QThread{
    Q_OBJECT

private:
    SerialPort &port;
    Protocol &protocol;
    Receiver *receiver = nullptr;
    bool keep_processing = true;
    bool connected = false;
    bool findDevice();
public:
    Sender(SerialPort &port, Protocol &protocol);
    ~Sender() override;
    void run() override;
};


#endif //__SENDER_H__
