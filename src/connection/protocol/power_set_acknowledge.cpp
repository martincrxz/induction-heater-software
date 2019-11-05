
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "power_set_acknowledge.h"
#include "endianness_config.h"

PowerSetAcknowledge::PowerSetAcknowledge(QByteArray &buff):
        IncomingMessage(POWER_SET_ACKNOWLEDGE) {
    uint32_t aux = letoh32(*((uint32_t *) &buff.data()[2]));
    this->data = aux;
}

int PowerSetAcknowledge::getData() {
    return data;
}