/*
 * Created by Federico Manuel Gomez Peter
 * on 21/9/19.
 */

#include <iostream>
#include <logger/logger.h>
#include "protocol.h"
#include "ping_message.h"
#include "pong_message.h"

Protocol::Protocol() {}

QByteArray Protocol::translate(MicroMessage *msg) {
    return std::move(msg->serialize());
}

std::shared_ptr<MicroMessage> Protocol::translate(QByteArray &buff) {
    switch (buff[ID_POSITION]) {
        case PING_ID:
            return std::shared_ptr<MicroMessage>(new PingMessage());
        case PONG_ID:
            return std::shared_ptr<MicroMessage>(new PongMessage(buff));
        default:
            Logger::warning("Mensaje inválido");
    }
    return std::shared_ptr<MicroMessage>();
}


