
/*
 * Created by Federico Manuel Gomez Peter
 * on 11/9/19.
 */
#include <QtCore>

#include "logger_info.h"

LoggerInfo::LoggerInfo(std::string &msg): Message(msg) {

}

void LoggerInfo::print() {
    qInfo() << this->msg.data();
}

bool LoggerInfo::quit() {
    return false;
}
