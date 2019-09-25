//
// Created by Martín García on 04/09/2019.
//

#include <logger/logger.h>
#include "protocol/micro_message.h"
#include "sender.h"
#include "serialport.h"
#include "protocol/ping_message.h"
#include "protocol/pong_message.h"

Sender::~Sender() {
    keep_processing = false;
    this->wait();
}

void Sender::run(){
    while (keep_processing) {
        if (!connected) {
            /*
             * debo liberar recursos si el receiver se desconectó
             */
            delete receiver;
            if (findDevice()) {
                receiver = new Receiver(&this->port);
                receiver->start();
            } else {
                Logger::debug("No se encontró dispositivo para conectarse.");
                QThread::msleep(5000);
            }
        } else {
            // send
        }
    }
}

bool Sender::findDevice() {
    auto portsInfo = QSerialPortInfo::availablePorts();
    for (auto &info: portsInfo) {
        Logger::info("Conectando a: " + info.portName().toStdString());
        this->port.setPort(info);
        if(this->port.open(QIODevice::ReadWrite)) {
            PingMessage ping;
            QByteArray msg_to_send = this->protocol.translate(&ping);
            this->port.send(msg_to_send);
            QByteArray response;
            if (this->port.receive(response)) {
                std::shared_ptr<MicroMessage> res(this->protocol.translate(
                        response));
                if (res->getId() == PONG_ID &&
                    ((PongMessage *) &(*res))->isConnected() ) {
                    Logger::info("Dispositivo conectado");
                    return true;
                } else {
                    port.close();
                }
            } else {
                port.close();
            }
        }
    }
    return false;
}

Sender::Sender(SerialPort &port, Protocol &protocol):   port(port),
                                                        protocol(protocol) {}
