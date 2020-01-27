
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __SET_POWER_H__
#define __SET_POWER_H__

#include "outgoing_message.h"

class SetPower: public OutgoingMessage {
public:
    SetPower(unsigned char taps);
    virtual ~SetPower() = default;
    QByteArray serialize() override;

private:
    unsigned char taps;
};


#endif // __SET_POWER_H__
