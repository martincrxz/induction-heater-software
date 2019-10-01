
/*
 * Created by Federico Manuel Gomez Peter
 * on 23/9/19.
 */

#ifndef __PING_MESSAGE_H__
#define __PING_MESSAGE_H__

#include <cstdint>
#include "micro_message.h"

class PingMessage: public MicroMessage {
private:
    uint8_t challenge{0x01};
public:
    PingMessage();
    virtual ~PingMessage() = default;
    QByteArray serialize() override;
};


#endif // __PING_MESSAGE_H__
