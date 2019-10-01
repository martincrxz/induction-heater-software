//
// Created by Martín García on 04/09/2019.
//

#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include <iostream>

#include <QThread>
#include <QSerialPort>

#include "protocol/protocol.h"

class Receiver : public QThread{
    Q_OBJECT

private:
    QSerialPort &port;
    Protocol protocol;
    bool keep_processing = true;

public:
    explicit Receiver(QSerialPort &port);
    ~Receiver() override;
    void run() override;
};


#endif //__RECEIVER_H__
