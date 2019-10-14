
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __POWER_SET_ACKNOWLEDGE_H__
#define __POWER_SET_ACKNOWLEDGE_H__


#include "micro_message.h"

class PowerSetAcknowledge: public MicroMessage {
public:
    PowerSetAcknowledge();
    virtual ~PowerSetAcknowledge() = default;
    QByteArray serialize() override;
};


#endif // __POWER_SET_ACKNOWLEDGE_H__
