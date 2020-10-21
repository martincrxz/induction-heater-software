
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include <QString>
#include "src/messages.h"
#include "thermocouple_fault.h"

static const char *faultMessages[] = {
        THERMOCOUPLE_ERR_MSG_CJ_TEMP_OUT_OF_RANGE,
        THERMOCOUPLE_ERR_MSG_TEMP_OUT_OF_RANGE,
        THERMOCOUPLE_ERR_MSG_CJ_TMP_OVER_LIMIT,
        THERMOCOUPLE_ERR_MSG_CJ_TMP_UNDER_LIMIT,
        THERMOCOUPLE_ERR_MSG_TMP_OVER_LIMIT,
        THERMOCOUPLE_ERR_MSG_TMP_UNDER_LIMIT,
        THERMOCOUPLE_ERR_MSG_OVER_VOLTAGE,
        THERMOCOUPLE_ERR_MSG_OPEN_CIRCUIT
};

ThermocoupleFault::ThermocoupleFault(QByteArray buff):
    IncomingMessage(THERMOCOUPLE_FAULT) {
    fault = (thermocouple_fault_t)(int)buff[2];
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
            return QString(THERMOCOUPLE_ERR_MSG_THERMOCOUPLE_TYPE_NOT_SUPPORTED);
    }
}
