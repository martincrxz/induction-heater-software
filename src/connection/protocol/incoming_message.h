/*
 * Created by Federico Manuel Gomez Peter
 * on 04/11/19.
 */

#ifndef __INCOMING_MESSAGE_H__
#define __INCOMING_MESSAGE_H__

#include <QtCore/QByteArray>

#include "micro_message.h"

class IncomingMessage: public MicroMessage {
public:
    explicit IncomingMessage(message_id id);
    virtual ~IncomingMessage() = default;
    QByteArray serialize() override;
    std::uint64_t getTimestamp();

private:
    std::uint64_t timestamp;
};


#endif // __INCOMING_MESSAGE_H__
