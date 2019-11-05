/*
 * Created by Federico Manuel Gomez Peter
 * on 04/11/19.
 */

#ifndef __OUTGOING_MESSAGE_H__
#define __OUTGOING_MESSAGE_H__

#include <QtCore/QByteArray>

#include "micro_message.h"

class OutgoingMessage: public MicroMessage {
public:
    explicit OutgoingMessage(message_id id);
    virtual ~OutgoingMessage() = default;
};


#endif // __OUTGOING_MESSAGE_H__
