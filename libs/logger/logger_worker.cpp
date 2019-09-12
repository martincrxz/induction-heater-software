
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#include "logger_worker.h"
#include <QtCore>
#include <logger/message/logger_quit.h>

LoggerWorker::~LoggerWorker() {
    this->stop();
    this->queue.close();
}

void LoggerWorker::run() {
    while (keep_processing) {
        std::shared_ptr<Message> msg;
        queue.pop(msg, true);
        if (msg->quit()) {
            keep_processing = false;
        } else {
            msg->print();
        }

    }
}

void LoggerWorker::stop() {
    std::shared_ptr<Message> ptr(new LoggerQuit());
    this->queue.push(ptr);
}

void LoggerWorker::pushMessage(std::shared_ptr<Message> msg) {
    this->queue.push(msg);
}
