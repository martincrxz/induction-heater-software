//
// Created by Martín García on 04/09/2019.
//

#ifndef __COMMUNICATOR_WORKER_H__
#define __COMMUNICATOR_WORKER_H__

#include <iostream>

#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "exception.h"

class CommunicatorWorker : public QThread{
    Q_OBJECT
private:
    QSerialPort *port;
    bool keep_processing = true;
public:
    CommunicatorWorker();
    ~CommunicatorWorker() override;
    void run() override;

};


#endif //__COMMUNICATOR_WORKER_H__
