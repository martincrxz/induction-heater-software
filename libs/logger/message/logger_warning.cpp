
/*
 * Created by Federico Manuel Gomez Peter
 * on 11/9/19.
 */

#include <QtCore>

#include "logger_warning.h"

LoggerWarning::LoggerWarning(std::string &msg) : Message(msg) {}

void LoggerWarning::print() {
    qWarning() << this->msg.data();
}

bool LoggerWarning::quit() {
    return false;
}
