
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "cold_junction_reading.h"
#include "endianness_config.h"

#define OFFSET 16
#define RESERVED_BITS 2
#define VALUE_MASK 0x1fff
#define SIGN_POSITION 13
#define DIVISOR 64.0

ColdJunctionReading::ColdJunctionReading(QByteArray &buff):
        MicroMessage(COLD_JUNCTION_READING) {
    uint32_t dataBits = betoh32(*((uint32_t *) &buff.data()[2]));
    float temp = ((dataBits >> OFFSET) >> RESERVED_BITS) & VALUE_MASK;
    int sign = 1 - 2 * ((((dataBits >> OFFSET) >> RESERVED_BITS)
            & (1 << SIGN_POSITION))>>SIGN_POSITION);
    this->data = (float) (sign * temp / DIVISOR);
}

QByteArray ColdJunctionReading::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = COLD_JUNCTION_READING;
    // It does not really make sense to implement this function for this type of message.
    return ret;
}

float ColdJunctionReading::getData() {
    return data;
}
