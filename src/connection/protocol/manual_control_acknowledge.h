
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __MANUAL_CONTROL_ACKNOWLEDGE_H__
#define __MANUAL_CONTROL_ACKNOWLEDGE_H__


#include "micro_message.h"

class ManualControlAcknowledge : public MicroMessage {
public:
    ManualControlAcknowledge();
    virtual ~ManualControlAcknowledge() = default;
    QByteArray serialize() override;
};


#endif // __MANUAL_CONTROL_ACKNOWLEDGE_H__
