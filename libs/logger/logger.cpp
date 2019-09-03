
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#include "logger.h"

std::unique_ptr<Logger> Logger::instance = nullptr;

Logger::Logger() {
    this->worker.start();
}

void Logger::init(const std::string &filename) {
    if ( instance == nullptr) {
        instance = std::unique_ptr<Logger>(new Logger());
    }
}

void Logger::info(const std::string &msg) {
    instance->worker.info(msg);
}

Logger::~Logger() {
    instance->worker.stop();
    instance->worker.wait();
}
