
/*
 * Created by Federico Manuel Gomez Peter
 * on 11/9/19.
 */

#ifndef __LOGGER_WARNING_H__
#define __LOGGER_WARNING_H__

#include "message.h"

class LoggerWarning: public Message {
public:
    LoggerWarning(std::string &msg);
    virtual ~LoggerWarning() = default;
    void print() override;
    bool quit() override;
};


#endif // __LOGGER_WARNING_H__
