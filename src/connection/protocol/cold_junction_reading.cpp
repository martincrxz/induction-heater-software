
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "cold_junction_reading.h"

ColdJunctionReading::ColdJunctionReading():
        MicroMessage(COLD_JUNCTION_READING) {}

QByteArray ColdJunctionReading::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = COLD_JUNCTION_READING;
    return ret;
}
