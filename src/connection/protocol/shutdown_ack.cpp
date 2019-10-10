
/*
 * Created by Federico Manuel Gomez Peter
 * on 24/9/19.
 */

#include "shutdown_ack.h"

ShutdownAcknowledge::ShutdownAcknowledge(): MicroMessage(SHUTDOWN_ACK_ID){}

QByteArray ShutdownAcknowledge::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = SHUTDOWN_ACK_ID;
    return ret;
}
