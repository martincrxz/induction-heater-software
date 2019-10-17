
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "cold_junction_reading.h"
#include "apple_endian.h"

ColdJunctionReading::ColdJunctionReading(QByteArray &buff):
        MicroMessage(COLD_JUNCTION_READING) {
    uint32_t aux = le32toh(*((uint32_t *) &buff.data()[2]));
    this->data = aux;
}

QByteArray ColdJunctionReading::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = COLD_JUNCTION_READING;
    uint32_t aux = htole32(this->data);
    memcpy(&ret.data()[2], (char *)&aux, 4);
    return ret;
}

float ColdJunctionReading::getData() {
    return data;
}
