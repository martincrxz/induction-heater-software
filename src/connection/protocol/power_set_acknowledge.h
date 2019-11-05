
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __POWER_SET_ACKNOWLEDGE_H__
#define __POWER_SET_ACKNOWLEDGE_H__


#include "incoming_message.h"

class PowerSetAcknowledge: public IncomingMessage {
private:
    int data;
public:
    PowerSetAcknowledge(QByteArray &);
    virtual ~PowerSetAcknowledge() = default;
    int getData();
};


#endif // __POWER_SET_ACKNOWLEDGE_H__
