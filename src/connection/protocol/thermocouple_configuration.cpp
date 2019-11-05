
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "thermocouple_configuration.h"

ThermocoupleConfiguration::ThermocoupleConfiguration():
    OutgoingMessage(THERMOCOUPLE_CONFIGURATION) {}

void ThermocoupleConfiguration::setType(thermocouple_type_t typeToSet){
    type = typeToSet;
}

QByteArray ThermocoupleConfiguration::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = THERMOCOUPLE_CONFIGURATION;
    ret[2] = FAUL_CLEAR_MASK & faultClear;
    ret[3] = type;
    return ret;
}

