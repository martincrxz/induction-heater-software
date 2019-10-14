
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "power_set_acknowledge.h"

QByteArray PowerSetAcknowledge::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = POWER_SET_ACKNOWLEDGE;
    return ret;
}

PowerSetAcknowledge::PowerSetAcknowledge():
        MicroMessage(POWER_SET_ACKNOWLEDGE) {}
