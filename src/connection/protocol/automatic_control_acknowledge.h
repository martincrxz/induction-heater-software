
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __AUTOMATIC_CONTROL_ACKNOWLEDGE_H__
#define __AUTOMATIC_CONTROL_ACKNOWLEDGE_H__


#include "incoming_message.h"

class AutomaticControlAcknowledge: public IncomingMessage {
public:
    AutomaticControlAcknowledge();
    virtual ~AutomaticControlAcknowledge() = default;
};


#endif // __AUTOMATIC_CONTROL_ACKNOWLEDGE_H__
