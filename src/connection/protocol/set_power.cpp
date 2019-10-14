
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "set_power.h"

SetPower::SetPower(): MicroMessage(SET_POWER) {}

QByteArray SetPower::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = SET_POWER;
    return ret;
}
