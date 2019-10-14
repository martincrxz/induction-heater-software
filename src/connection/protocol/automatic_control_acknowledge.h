
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __AUTOMATIC_CONTROL_ACKNOWLEDGE_H__
#define __AUTOMATIC_CONTROL_ACKNOWLEDGE_H__


#include "micro_message.h"

class AutomaticControlAcknowledge: public MicroMessage {
public:
    AutomaticControlAcknowledge();
    virtual ~AutomaticControlAcknowledge() = default;
    QByteArray serialize() override;
};


#endif // __AUTOMATIC_CONTROL_ACKNOWLEDGE_H__
