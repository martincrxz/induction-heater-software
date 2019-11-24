/*
 * Created by Federico Manuel Gomez Peter
 * on 24/11/19.
 */

#include <QtCore>

#include "logger_critical.h"

LoggerCritical::LoggerCritical(std::string &msg) : LoggerMessage(msg) {}

void LoggerCritical::print() {
    qCritical() << this->msg.data();
}

bool LoggerCritical::quit() {
    return false;
}
