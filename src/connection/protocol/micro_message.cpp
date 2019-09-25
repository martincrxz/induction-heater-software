
/*
 * Created by Federico Manuel Gomez Peter
 * on 22/9/19.
 */

#include "micro_message.h"

MicroMessage::MicroMessage(message_id id): id(id) {}

message_id MicroMessage::getId() {
    return this->id;
}


