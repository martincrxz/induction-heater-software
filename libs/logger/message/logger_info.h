
/*
 * Created by Federico Manuel Gomez Peter
 * on 11/9/19.
 */

#ifndef __INFO_H__
#define __INFO_H__

#include <string>

#include "logger_message.h"

class LoggerInfo: public LoggerMessage {
public:
    explicit LoggerInfo(std::string &msg);
    virtual ~LoggerInfo() = default;
    void print() override;
    bool quit() override;
};


#endif // __INFO_H__
