//
// Created by Martín García on 04/09/2019.
//

#ifndef __SENDER_H__
#define __SENDER_H__

#include <iostream>

#include <QThread>
#include <QSerialPort>

class Sender : public QThread{
    Q_OBJECT

private:
    QSerialPort &port;
    bool keep_processing = true;

public:
    explicit Sender(QSerialPort &port) : port(port) {};
    ~Sender() override;
    void run() override;
};


#endif //__SENDER_H__
