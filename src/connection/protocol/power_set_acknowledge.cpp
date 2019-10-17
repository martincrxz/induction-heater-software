
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "power_set_acknowledge.h"
#include "apple_endian.h"

QByteArray PowerSetAcknowledge::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = POWER_SET_ACKNOWLEDGE;
    uint32_t aux = htole32(this->data);
    memcpy(&ret.data()[2], (char *)&aux, 4);
    return ret;
}

PowerSetAcknowledge::PowerSetAcknowledge(QByteArray &buff):
        MicroMessage(POWER_SET_ACKNOWLEDGE) {
    uint32_t aux = le32toh(*((uint32_t *) &buff.data()[2]));
    this->data = aux;
}

int PowerSetAcknowledge::getData() {
    return data;
}