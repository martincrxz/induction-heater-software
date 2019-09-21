//
// Created by Martín García on 04/09/2019.
//

#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include <iostream>

#include <QThread>
#include <QSerialPort>

class Receiver : public QThread{
    Q_OBJECT

private:
    QSerialPort *port;
    bool keep_processing = true;

public:
    explicit Receiver(QSerialPort *port) : port(port) {};
    ~Receiver() override;
    void run() override;
};


#endif //__RECEIVER_H__
