
/*
 * Created by Federico Manuel Gomez Peter
 * on 23/9/19.
 */

#include "ping_message.h"

PingMessage::PingMessage() : MicroMessage(PING_ID){}

QByteArray&& PingMessage::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = PING_ID;
    return std::move(ret);
}
