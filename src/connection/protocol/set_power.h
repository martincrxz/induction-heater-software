
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __SET_POWER_H__
#define __SET_POWER_H__


#include "micro_message.h"

class SetPower: public MicroMessage {
public:
    SetPower();
    virtual ~SetPower() = default;
    QByteArray serialize() override;
};


#endif // __SET_POWER_H__
