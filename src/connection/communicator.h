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

class Communicator : public QObject{
    Q_OBJECT
private:
    SerialPort *port = nullptr;

public:
    explicit Communicator(QObject *parent);
    ~Communicator() override;

public slots:
    void write(std::shared_ptr<MicroMessage> msg);
};


#endif // __COMMUNICATOR_H__
