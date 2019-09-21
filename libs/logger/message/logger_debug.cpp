
/*
 * Created by Federico Manuel Gomez Peter
 * on 11/9/19.
 */

#include <QtCore>

#include "logger_debug.h"

LoggerDebug::LoggerDebug(std::string &msg) : LoggerMessage(msg) {}

void LoggerDebug::print() {
    qDebug() << this->msg.data();
}

bool LoggerDebug::quit() {
    return false;
}
