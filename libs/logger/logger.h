
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <memory>

#include "logger_worker.h"

class Logger {
private:
    LoggerWorker worker;
    static std::unique_ptr<Logger> instance;
    Logger();
public:
    static void init(const std::string &filename);
    static void info(const std::string &msg);
    virtual ~Logger();
};


#endif // __LOGGER_H__
