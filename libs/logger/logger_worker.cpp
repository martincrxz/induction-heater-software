
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#include "logger_worker.h"
#include <iostream>

LoggerWorker::~LoggerWorker() {
    this->stop();
    this->queue.close();
}

void LoggerWorker::run() {
    while (keep_processing) {
        std::string msg;
        queue.pop(msg, true);
        if (msg == "quit") {
            keep_processing = false;
        }
        std::cout << msg << std::endl;
    }
}

void LoggerWorker::stop() {
    this->queue.push("quit");
}

void LoggerWorker::info(const std::string &msg) {
    this->queue.push(msg);
}

