
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "set_automatic_control.h"

SetAutomaticControl::SetAutomaticControl():
            MicroMessage(SET_AUTOMATIC_CONTROL) {}

QByteArray SetAutomaticControl::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = SET_AUTOMATIC_CONTROL;
    return ret;
}


