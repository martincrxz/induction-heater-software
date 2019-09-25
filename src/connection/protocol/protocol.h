
/*
 * Created by Federico Manuel Gomez Peter
 * on 21/9/19.
 */

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


#include <memory>
#include "micro_message.h"
#include "../serialport.h"

#define ID_POSITION 1

class Protocol {
public:
    Protocol();
    Protocol & operator<<(std::string& msg);
    QByteArray&& translate(MicroMessage *msg);
    std::shared_ptr<MicroMessage> translate(QByteArray &buff);
};


#endif // __PROTOCOL_H__
