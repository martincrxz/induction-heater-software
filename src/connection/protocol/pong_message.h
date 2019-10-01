
/*
 * Created by Federico Manuel Gomez Peter
 * on 24/9/19.
 */

#ifndef __PONG_MESSAGE_H__
#define __PONG_MESSAGE_H__

#include <QtCore/QByteArray>
#include "micro_message.h"

class PongMessage: public MicroMessage {
private:
    uint8_t  challenge;
public:
    explicit PongMessage(QByteArray &buff);
    bool isConnected();
    QByteArray serialize() override;
};


#endif // __PONG_MESSAGE_H__
