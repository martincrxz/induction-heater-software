
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __MANUAL_CONTROL_ACKNOWLEDGE_H__
#define __MANUAL_CONTROL_ACKNOWLEDGE_H__


#include "incoming_message.h"

class ManualControlAcknowledge : public IncomingMessage {
public:
    ManualControlAcknowledge();
    virtual ~ManualControlAcknowledge() = default;
};


#endif // __MANUAL_CONTROL_ACKNOWLEDGE_H__
