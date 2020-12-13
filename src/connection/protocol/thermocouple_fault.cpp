
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include <QString>
#include "messages.h"
#include "thermocouple_fault.h"

static std::vector<const char *>faultMessages = {
        THERMOCOUPLE_ERR_MSG_CJ_TEMP_OUT_OF_RANGE,
        THERMOCOUPLE_ERR_MSG_TEMP_OUT_OF_RANGE,
        THERMOCOUPLE_ERR_MSG_CJ_TMP_OVER_LIMIT,
        THERMOCOUPLE_ERR_MSG_CJ_TMP_UNDER_LIMIT,
        THERMOCOUPLE_ERR_MSG_TMP_OVER_LIMIT,
        THERMOCOUPLE_ERR_MSG_TMP_UNDER_LIMIT,
        THERMOCOUPLE_ERR_MSG_OVER_VOLTAGE,
        THERMOCOUPLE_ERR_MSG_OPEN_CIRCUIT
};

static std::vector<thermocouple_fault_t> possible_errors = {
    CJRANGE_FAULT,
    TCRANGE_FAULT,
    CJHIGH_FAULT,
    CJLOW_FAULT,
    TCHIGH_FAULT,
    TCLOW_FAULT,
    OVUV_FAULT,
    OPEN_FAULT
};

ThermocoupleFault::ThermocoupleFault(QByteArray buff):
    IncomingMessage(THERMOCOUPLE_FAULT) {
    fault = (thermocouple_fault_t)(int)buff[2];
}

std::vector<QString> ThermocoupleFault::error() {
    std::vector<QString> result;
    for(auto error_mask : possible_errors) {
        switch (this->fault & error_mask){
            case CJRANGE_FAULT:
                result.emplace_back(faultMessages[0]);
            case TCRANGE_FAULT:
                result.emplace_back(faultMessages[1]);
            case CJHIGH_FAULT:
                result.emplace_back(faultMessages[2]);
            case CJLOW_FAULT:
                result.emplace_back(faultMessages[3]);
            case TCHIGH_FAULT:
                result.emplace_back(faultMessages[4]);
            case TCLOW_FAULT:
                result.emplace_back(faultMessages[5]);
            case OVUV_FAULT:
                result.emplace_back(faultMessages[6]);
            case OPEN_FAULT:
                result.emplace_back(faultMessages[7]);
            default:
                result.emplace_back(THERMOCOUPLE_ERR_MSG_THERMOCOUPLE_TYPE_NOT_SUPPORTED);
        }
    }
    return std::move(result);
}
