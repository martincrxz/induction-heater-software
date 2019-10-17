
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __POWER_SET_ACKNOWLEDGE_H__
#define __POWER_SET_ACKNOWLEDGE_H__


#include "micro_message.h"

class PowerSetAcknowledge: public MicroMessage {
private:
    int data;
public:
    PowerSetAcknowledge(QByteArray &);
    virtual ~PowerSetAcknowledge() = default;
    QByteArray serialize() override;
    int getData();
};


#endif // __POWER_SET_ACKNOWLEDGE_H__
