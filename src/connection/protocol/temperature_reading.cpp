
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "temperature_reading.h"

TemperatureReading::TemperatureReading(): MicroMessage(TEMPERATURE_READING) {

}

QByteArray TemperatureReading::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = TEMPERATURE_READING;
    return ret;
}

