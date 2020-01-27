
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#include <QtCore/QDateTime>
#include <iostream>
#include <fstream>
#include <sstream>

#include "logger.h"
#include "message/logger_info.h"
#include "message/logger_critical.h"
#include "message/logger_warning.h"
#include "message/logger_debug.h"

/**
 *  Variable "global" (solo tiene scope en este archivo)
 *  que apunta al archivo de loggeo.
 */
static std::fstream log_file(FILE_NAME, std::ios_base::out | std::ios_base::trunc);
/**
 * handler para formatear los mensajes de salida del log.
 * @param type
 * @param context
 * @param msg
 */
void messageHandler(QtMsgType type, const QMessageLogContext &context,
        const QString &msg);

Logger::Logger() {
    this->worker.start();
}
Logger& Logger::instance() {
    static Logger s;
    return s;
}
void Logger::init() {
    Logger::instance();
    qInstallMessageHandler(messageHandler);
}

void Logger::info(std::string msg) {
    std::shared_ptr<LoggerMessage> ptr(new LoggerInfo(msg));
    Logger::instance().worker.pushMessage(ptr);
}

Logger::~Logger() {
    Logger::instance().worker.stop();
    Logger::instance().worker.wait();
}

void Logger::debug(std::string msg) {
    std::shared_ptr<LoggerMessage> ptr(new LoggerDebug(msg));
    Logger::instance().worker.pushMessage(ptr);
}

void Logger::warning(std::string msg) {
    std::shared_ptr<LoggerMessage> ptr(new LoggerWarning(msg));
    Logger::instance().worker.pushMessage(ptr);
}

void Logger::critical(std::string msg) {
    LoggerCritical *log = new LoggerCritical(msg);
    std::shared_ptr<LoggerMessage> ptr(log);
    Logger::instance().worker.pushMessage(ptr);
}

void messageHandler(QtMsgType type, 
                    __attribute__((unused)) const QMessageLogContext &context,
                    const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    std::string currentDatetime = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss").toStdString();
    std::ostringstream ss;
    switch (type) {
        case QtDebugMsg:
            ss  << currentDatetime.data() 
                << " [DEBUG] "
                << localMsg.constData();
            break;
        case QtInfoMsg:
            ss  << currentDatetime.data() 
                << " [INFO] "
                << localMsg.constData();
            break;
        case QtWarningMsg:
            ss  << currentDatetime.data() 
                << " [WARNING] "
                << localMsg.constData();
            break;
        case QtCriticalMsg:
            ss  << currentDatetime.data() 
                << " [CRITICAL] "
                << localMsg.constData();
            break;
        case QtFatalMsg:
            ss  << currentDatetime.data() 
                << " [FATAL] "
                << localMsg.constData();
            break;
    }
    log_file  << ss.str() << std::endl;
    std::cerr << ss.str() << std::endl;
}
