
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include <QString>

#include "thermocouple_fault.h"

const char *faultMessages[] = {
        "Cold junction temperature out of range.",
        "Temperature out of range.",
        "Cold junction temperature over high limit.",
        "Cold junction temperature under low limit.",
        "Temperature over high limit.",
        "Temperature under low limit.",
        "Over voltage",
        "Open thermocouple."
};

ThermocoupleFault::ThermocoupleFault(QByteArray buff):
    MicroMessage(THERMOCOUPLE_FAULT) {
    fault = (thermocouple_fault_t)(int)buff[2];
}

QByteArray ThermocoupleFault::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = THERMOCOUPLE_FAULT;
    ret[2] = fault;
    return ret;
}

QString ThermocoupleFault::error() {
    switch (this->fault){
        case CJRANGE_FAULT:
            return QString(faultMessages[0]);
        case TCRANGE_FAULT:
            return QString(faultMessages[1]);
        case CJHIGH_FAULT:
            return QString(faultMessages[2]);
        case CJLOW_FAULT:
            return QString(faultMessages[3]);
        case TCHIGH_FAULT:
            return QString(faultMessages[4]);
        case TCLOW_FAULT:
            return QString(faultMessages[5]);
        case OVUV_FAULT:
            return QString(faultMessages[6]);
        case OPEN_FAULT:
            return QString(faultMessages[7]);
        default:
            return QString("Non-supported thermocouple error");
    }
}