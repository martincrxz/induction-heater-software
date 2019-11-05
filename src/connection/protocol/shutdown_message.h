
/*
 * Created by Federico Manuel Gomez Peter
 * on 6/10/19.
 */

#ifndef __SHUTDOWN_MESSAGE_H__
#define __SHUTDOWN_MESSAGE_H__


#include "outgoing_message.h"

class ShutdownMessage: public OutgoingMessage {
public:
    ShutdownMessage();
    virtual ~ShutdownMessage() = default;
    QByteArray serialize() override;
};


#endif // __SHUTDOWN_MESSAGE_H__
