
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __SET_AUTOMATIC_CONTROL_H__
#define __SET_AUTOMATIC_CONTROL_H__


#include "micro_message.h"

class SetAutomaticControl: public MicroMessage {
public:
    SetAutomaticControl();
    virtual ~SetAutomaticControl() = default;
    QByteArray serialize() override;
};


#endif // __set_automatic_control_H__
