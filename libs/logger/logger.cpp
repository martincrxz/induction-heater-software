
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#include "logger.h"
#include "message/logger_info.h"
#include "message/logger_debug.h"
#include "message/logger_warning.h"

std::unique_ptr<Logger> Logger::instance = nullptr;

Logger::Logger() {
    this->worker.start();
}

void Logger::init(const std::string &filename) {
    if ( instance == nullptr) {
        instance = std::unique_ptr<Logger>(new Logger());
    }
}

void Logger::info(std::string msg) {
    std::shared_ptr<Message> ptr(new LoggerInfo(msg));
    instance->worker.pushMessage(ptr);
}

Logger::~Logger() {
    instance->worker.stop();
    instance->worker.wait();
}

void Logger::debug(std::string msg) {
    std::shared_ptr<Message> ptr(new LoggerDebug(msg));
    instance->worker.pushMessage(ptr);
}

void Logger::warning(std::string msg) {
    std::shared_ptr<Message> ptr(new LoggerWarning(msg));
    instance->worker.pushMessage(ptr);
}
