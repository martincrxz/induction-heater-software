
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "thermocouple_configuration_acknowledge.h"

ThermocoupleConfigurationAcknowledge::ThermocoupleConfigurationAcknowledge():
    MicroMessage(THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE) {}

QByteArray ThermocoupleConfigurationAcknowledge::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE;
    return ret;
}
