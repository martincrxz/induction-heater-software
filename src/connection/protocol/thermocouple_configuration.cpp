
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "thermocouple_configuration.h"

ThermocoupleConfiguration::ThermocoupleConfiguration():
    MicroMessage(THERMOCOUPLE_CONFIGURATION) {}

QByteArray ThermocoupleConfiguration::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = THERMOCOUPLE_CONFIGURATION;
    return ret;
}

