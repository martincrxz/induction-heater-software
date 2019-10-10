
/*
 * Created by Federico Manuel Gomez Peter
 * on 24/9/19.
 */

#ifndef __SHUTDOWN_ACK_H__
#define __SHUTDOWN_ACK_H__

#include <QtCore/QByteArray>
#include "micro_message.h"

class ShutdownAcknowledge: public MicroMessage {

public:
    explicit ShutdownAcknowledge();
    QByteArray serialize() override;
};


#endif // __SHUTDOWN_ACK_H__
