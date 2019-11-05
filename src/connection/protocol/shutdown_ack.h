
/*
 * Created by Federico Manuel Gomez Peter
 * on 24/9/19.
 */

#ifndef __SHUTDOWN_ACK_H__
#define __SHUTDOWN_ACK_H__

#include <QtCore/QByteArray>
#include "incoming_message.h"

class ShutdownAcknowledge: public IncomingMessage {

public:
    explicit ShutdownAcknowledge();
    virtual ~ShutdownAcknowledge() = default;
};


#endif // __SHUTDOWN_ACK_H__
