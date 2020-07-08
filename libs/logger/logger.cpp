
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */
#include <atomic>
#include <fstream>
#include <iostream>
#include <QtCore/QDateTime>
#include <sstream>
#include <vector>

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
// Variable atómica para evitar race conditions
static std::atomic<unsigned char> current_level{INFO | WARNING | CRITICAL | FATAL | DEBUG};
/**
 * handler para formatear los mensajes de salida del log.
 * @param type
 * @param context
 * @param msg
 */
void messageHandler(QtMsgType type, const QMessageLogContext &context,
        const QString &msg);
/**
 * @brief Transforma el QtMsgType en un LogLevel. Esto se hizo
 * para reordenar la prioridad de los niveles de loggeo
 * @param type
 * @return
 */
static LogLevel toLogLevel(const QtMsgType &type);

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

Logger::~Logger() {
    Logger::instance().worker.stop();
    Logger::instance().worker.wait();
}

void Logger::parseString(const char *fmt, va_list &args, std::string &msg) {
    va_list args_copy;
    va_copy(args_copy, args);
    try {
        std::size_t size = std::vsnprintf(nullptr, 0, fmt, args) + 1;
        std::vector<char> buff(size);
        std::vsnprintf(buff.data(), size, fmt, args_copy);
        msg = buff.data();
        va_end(args_copy);
    } catch (...) {
        va_end(args_copy);
    }
}

void Logger::info(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg;
    Logger::parseString(fmt, args, msg);
    va_end(args);

    std::shared_ptr<LoggerMessage> ptr(new LoggerInfo(msg));
    Logger::instance().worker.pushMessage(ptr);
}


void Logger::debug(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg;
    Logger::parseString(fmt, args, msg);
    va_end(args);

    std::shared_ptr<LoggerMessage> ptr(new LoggerDebug(msg));
    Logger::instance().worker.pushMessage(ptr);
}

void Logger::warning(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg;
    Logger::parseString(fmt, args, msg);
    va_end(args);

    std::shared_ptr<LoggerMessage> ptr(new LoggerWarning(msg));
    Logger::instance().worker.pushMessage(ptr);
}

void Logger::critical(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg;
    Logger::parseString(fmt, args, msg);
    va_end(args);

    LoggerCritical *log = new LoggerCritical(msg);
    std::shared_ptr<LoggerMessage> ptr(log);
    Logger::instance().worker.pushMessage(ptr);
}

void Logger::logLevelChanged(uint8_t newConf)
{
    Logger::info("Logger levels changed");
    current_level = newConf;
}

LogLevel toLogLevel(const QtMsgType &type) {
    switch (type) {
    case QtDebugMsg:
        return DEBUG;
    case QtInfoMsg:
        return INFO;
    case QtWarningMsg:
        return WARNING;
    case QtCriticalMsg:
        return CRITICAL;
    case QtFatalMsg:
        return FATAL;
    default:
        return NOTHING;
    }
}
void messageHandler(QtMsgType type, 
                    __attribute__((unused)) const QMessageLogContext &context,
                    const QString &msg) {
    if (current_level & toLogLevel(type)) {
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
}
