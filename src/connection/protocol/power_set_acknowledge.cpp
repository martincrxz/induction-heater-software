
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "power_set_acknowledge.h"
//#include "endianness_config.h"

PowerSetAcknowledge::PowerSetAcknowledge(QByteArray &buff):
        IncomingMessage(POWER_SET_ACKNOWLEDGE) {
    std::uint8_t aux = buff[2];
    this->data = aux;
}

float PowerSetAcknowledge::getPower() {
    return 100 * (MAXIMUM_TAP - data) / MAXIMUM_TAP;
}

PowerSetAcknowledge::PowerSetAcknowledge(std::uint8_t power): IncomingMessage(POWER_SET_ACKNOWLEDGE), data(power) {

}
