/*
 * Created by Federico Manuel Gomez Peter
 * on 24/11/19.
 */

#ifndef __LOGGER_CRITICAL_H__
#define __LOGGER_CRITICAL_H__

#include "logger_message.h"

class LoggerCritical: public LoggerMessage {
public:
    LoggerCritical(std::string &msg);
    virtual ~LoggerCritical() = default;
    void print() override;
    bool quit() override;
};


#endif // __LOGGER_CRITICAL_H__
