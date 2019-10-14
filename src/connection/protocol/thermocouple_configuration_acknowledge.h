
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE_H__
#define __THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE_H__


#include "micro_message.h"

class ThermocoupleConfigurationAcknowledge: public MicroMessage {
public:
    ThermocoupleConfigurationAcknowledge();
    virtual ~ThermocoupleConfigurationAcknowledge() = default;
    QByteArray serialize() override;
};


#endif // __THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE_H__
