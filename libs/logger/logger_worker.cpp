
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#include "logger_worker.h"
#include <QtCore>
#include <logger/message/logger_quit.h>
#include <iostream>

LoggerWorker::~LoggerWorker() {
    this->stop();
    this->queue.close();
}

void LoggerWorker::run() {
    try {
        while (keep_processing) {
            std::shared_ptr<LoggerMessage> msg;
            queue.pop(msg, true);
            if (msg->quit()) {
                keep_processing = false;
            } else {
                msg->print();
            }
        }
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }  catch(...) {
        std::cerr << "Unknown error in LoggerWorker::run" << std::endl;
    }
}

void LoggerWorker::stop() {
    std::shared_ptr<LoggerMessage> ptr(new LoggerQuit());
    this->queue.push(ptr);
}

void LoggerWorker::pushMessage(std::shared_ptr<LoggerMessage> msg) {
    this->queue.push(msg);
}
