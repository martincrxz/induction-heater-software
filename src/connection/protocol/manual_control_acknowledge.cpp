
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "manual_control_acknowledge.h"

ManualControlAcknowledge::ManualControlAcknowledge():
            MicroMessage(MANUAL_CONTROL_ACKNOWLEDGE) {}

QByteArray ManualControlAcknowledge::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = MANUAL_CONTROL_ACKNOWLEDGE;
    return ret;
}

