
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __thermocouple_fault_H__
#define __thermocouple_fault_H__


#include "micro_message.h"

class ThermocoupleFault: public MicroMessage {
public:
    ThermocoupleFault();
    virtual ~ThermocoupleFault() = default;
    QByteArray serialize() override;
};


#endif // __thermocouple_fault_H__
