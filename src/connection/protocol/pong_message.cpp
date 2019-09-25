
/*
 * Created by Federico Manuel Gomez Peter
 * on 24/9/19.
 */

#include "pong_message.h"

#define CHALLENGE_SUCCESS 0x02
#define CHALLENGE_POSITION 1

PongMessage::PongMessage(QByteArray &buff): MicroMessage(PONG_ID),
                                           challenge(buff[CHALLENGE_POSITION]){}

bool PongMessage::isConnected() {
    return this->challenge == CHALLENGE_SUCCESS;
}

QByteArray&& PongMessage::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = PONG_ID;
    return std::move(ret);
}

