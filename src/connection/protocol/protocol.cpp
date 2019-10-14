/*
 * Created by Federico Manuel Gomez Peter
 * on 21/9/19.
 */

#include <iostream>
#include <logger/logger.h>
#include "protocol.h"
#include "shutdown_ack.h"
#include "temperature_reading.h"

Protocol::Protocol() {}

QByteArray Protocol::translate(std::shared_ptr<MicroMessage>msg) {
    return std::move(msg->serialize());
}

std::shared_ptr<MicroMessage> Protocol::translate(QByteArray &buff) {
    switch (buff[ID_POSITION]) {
        case SHUTDOWN_MESSAGE:
            return std::shared_ptr<MicroMessage>(new ShutdownAcknowledge());
        case TEMPERATURE_READING:
            return std::shared_ptr<MicroMessage>(new TemperatureReading(buff));
        default:
            Logger::warning("Invalid message");
            break;
    }
    return std::shared_ptr<MicroMessage>();
}


