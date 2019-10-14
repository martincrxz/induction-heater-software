
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __SET_MANUAL_CONTROL_H__
#define __SET_MANUAL_CONTROL_H__


#include "micro_message.h"

class SetManualControl: MicroMessage {
public:
    SetManualControl();
    virtual ~SetManualControl() = default;
    QByteArray serialize() override;
};


#endif // __SET_MANUAL_CONTROL_H__
