
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE_H__
#define __THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE_H__


#include "incoming_message.h"

class ThermocoupleConfigurationAcknowledge: public IncomingMessage {
public:
    ThermocoupleConfigurationAcknowledge();
    virtual ~ThermocoupleConfigurationAcknowledge() = default;
};


#endif // __THERMOCOUPLE_CONFIGURATION_ACKNOWLEDGE_H__
