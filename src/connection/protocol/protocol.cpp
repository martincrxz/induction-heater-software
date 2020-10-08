/*
 * Created by Federico Manuel Gomez Peter
 * on 21/9/19.
 */

#include <iostream>
#include <logger/logger.h>
#include <messages.h>

#include "protocol.h"
#include "shutdown_ack.h"
#include "temperature_reading.h"
#include "cold_junction_reading.h"
#include "power_set_acknowledge.h"
#include "manual_control_acknowledge.h"
#include "automatic_control_acknowledge.h"
#include "thermocouple_fault.h"
#include "thermocouple_configuration_acknowledge.h"

Protocol::Protocol() {}

QByteArray Protocol::translate(std::shared_ptr<MicroMessage>msg) {
    return std::move(msg->serialize());
}

std::shared_ptr<MicroMessage> Protocol::translate(QByteArray &buff) {
    switch (buff[ID_POSITION]) {
        case SHUTDOWN_ACKNOWLEDGE:
            return std::shared_ptr<MicroMessage>(new ShutdownAcknowledge());
        case TEMPERATURE_READING:
            return std::shared_ptr<MicroMessage>(new TemperatureReading(buff));
        case COLD_JUNCTION_READING:
            return std::shared_ptr<MicroMessage>(new ColdJunctionReading(buff));
        case THERMOCOUPLE_FAULT:
            return std::shared_ptr<ThermocoupleFault>(new ThermocoupleFault(buff));
        case THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE:
            return std::shared_ptr<MicroMessage>(new ThermocoupleConfigurationAcknowledge());
        case POWER_SET_ACKNOWLEDGE:
            return std::shared_ptr<MicroMessage>(new PowerSetAcknowledge(buff));
        case MANUAL_CONTROL_ACKNOWLEDGE:
            return std::shared_ptr<MicroMessage>(new ManualControlAcknowledge());
        case AUTOMATIC_CONTROL_ACKNOWLEDGE:
            return std::shared_ptr<MicroMessage>(new AutomaticControlAcknowledge());
        default:
            Logger::warning(PROTOCOL_INVALID_MSG_ERROR_MSG);
            break;
    }
    return std::shared_ptr<MicroMessage>();
}


