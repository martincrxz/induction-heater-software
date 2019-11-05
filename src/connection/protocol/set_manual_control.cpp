
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "set_manual_control.h"

SetManualControl::SetManualControl(): OutgoingMessage(SET_MANUAL_CONTROL) {}

QByteArray SetManualControl::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = SET_MANUAL_CONTROL;
    return ret;
}

