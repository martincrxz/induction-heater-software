
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "automatic_control_acknowledge.h"

AutomaticControlAcknowledge::AutomaticControlAcknowledge():
            MicroMessage(AUTOMATIC_CONTROL_ACKNOWLEDGE) {}

QByteArray AutomaticControlAcknowledge::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = AUTOMATIC_CONTROL_ACKNOWLEDGE;
    return ret;
}
