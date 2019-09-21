
/*
 * Created by Federico Manuel Gomez Peter
 * on 11/9/19.
 */

#ifndef __LOGGER_DEBUG_H__
#define __LOGGER_DEBUG_H__

#include "message.h"

class LoggerDebug: public Message {
public:
    LoggerDebug(std::string &msg);
    virtual ~LoggerDebug() = default;
    void print() override;
    bool quit() override;
};


#endif // __LOGGER_DEBUG_H__
