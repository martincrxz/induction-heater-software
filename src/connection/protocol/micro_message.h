
/*
 * Created by Federico Manuel Gomez Peter
 * on 22/9/19.
 */

#ifndef __MICRO_MESSAGE_H__
#define __MICRO_MESSAGE_H__

#include <QtCore/QByteArray>

#define MESSAGE_SEPARATOR 0x7E

typedef enum {
    TEMPERATURE_READING = 0x10, // to computer OK
    COLD_JUNCTION_READING = 0x11, // to computer OK
    THERMOCOUPLE_FAULT = 0x12, // to computer OK
    THERMOCOUPLE_CONFIGURATION = 0x13, // to uC
    THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE = 0x14, // to computer OK
    SET_POWER = 0x20, // to uC
    POWER_SET_ACKNOWLEDGE = 0x21, // to computer OK
    SET_AUTOMATIC_CONTROL = 0x30, // to uC
    AUTOMATIC_CONTROL_ACKNOWLEDGE = 0x31, // to computer OK
    SET_MANUAL_CONTROL = 0x32, // to uC
    MANUAL_CONTROL_ACKNOWLEDGE = 0x33, // to computer OK
    CURRENT_RMS_READING = 0x40, // OK
    CURRENT_FREQUENCY_READING = 0x41, // OK
    SHUTDOWN_MESSAGE = 0x50, // to uC
    SHUTDOWN_ACKNOWLEDGE = 0x51 // to computer OK
} message_id;

class MicroMessage {
private:
    message_id id;
public:
    explicit MicroMessage(message_id id);
    virtual ~MicroMessage() = default;
    /**
     * @brief devuelve el id de la clase (cada clase hija
     * tendrá un id distinto.
     * @return
     */
    message_id getId();
    /**
     * @brief función polimorfica que transforma el DTO en una tira de
     * bytes para ser enviado al puerto serie.
     * @return
     */
    virtual QByteArray serialize() = 0;
};


#endif // __MICRO_MESSAGE_H__
