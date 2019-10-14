
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __THERMOCOUPLE_CONFIGURATION_H__
#define __THERMOCOUPLE_CONFIGURATION_H__


#include "micro_message.h"

class ThermocoupleConfiguration: public MicroMessage {
public:
    ThermocoupleConfiguration();
    virtual ~ThermocoupleConfiguration() = default;
    QByteArray serialize() override;
};


#endif // __THERMOCOUPLE_CONFIGURATION_H__
