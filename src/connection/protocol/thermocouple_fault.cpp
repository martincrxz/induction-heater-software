
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "thermocouple_fault.h"

ThermocoupleFault::ThermocoupleFault(): MicroMessage(THERMOCOUPLE_FAULT) {

}

QByteArray ThermocoupleFault::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = THERMOCOUPLE_FAULT;
    return ret;
}
