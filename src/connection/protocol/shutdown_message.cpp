
/*
 * Created by Federico Manuel Gomez Peter
 * on 6/10/19.
 */

#include "shutdown_message.h"

ShutdownMessage::ShutdownMessage(): OutgoingMessage(SHUTDOWN_MESSAGE) {}

QByteArray ShutdownMessage::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = SHUTDOWN_MESSAGE;
    return ret;
}
