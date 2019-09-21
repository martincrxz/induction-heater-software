
/*
 * Created by Federico Manuel Gomez Peter
 * on 11/9/19.
 */

#ifndef __QUIT_H__
#define __QUIT_H__

#include "message.h"

class LoggerQuit: public Message {
public:
    LoggerQuit();
    virtual ~LoggerQuit() = default;
    void print() override;
    bool quit() override;
};


#endif // __QUIT_H__
