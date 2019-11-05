
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __THERMOCOUPLE_CONFIGURATION_H__
#define __THERMOCOUPLE_CONFIGURATION_H__

#include "outgoing_message.h"

#define FAUL_CLEAR_MASK 0x02

typedef enum {thermocouple_type_B = 0,
              thermocouple_type_E,
              thermocouple_type_J,
              thermocouple_type_K,
              thermocouple_type_N,
              thermocouple_type_R,
              thermocouple_type_S,
              thermocouple_type_T} thermocouple_type_t;

class ThermocoupleConfiguration: public OutgoingMessage {
private:
    thermocouple_type_t type = thermocouple_type_B;
    bool faultClear = false;
public:
    ThermocoupleConfiguration();
    virtual ~ThermocoupleConfiguration() = default;
    QByteArray serialize() override;
    void setType(thermocouple_type_t);
};


#endif // __THERMOCOUPLE_CONFIGURATION_H__
