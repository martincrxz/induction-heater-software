
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include <iostream>
#include "set_power.h"

SetPower::SetPower(unsigned char i) : OutgoingMessage(SET_POWER), taps(i) {}

QByteArray SetPower::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = SET_POWER;
    ret[2] = this->taps;
    return ret;
}
