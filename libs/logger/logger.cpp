
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#include <QtCore/QDateTime>
#include "logger.h"
#include "message/logger_info.h"
#include "message/logger_debug.h"
#include "message/logger_warning.h"

std::unique_ptr<Logger> Logger::instance = nullptr;
/**
 * handler para formatear los mensajes de salida del log.
 * @param type
 * @param context
 * @param msg
 */
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

Logger::Logger() {
    this->worker.start();
}

void Logger::init(const std::string &filename) {
    if ( instance == nullptr) {
        instance = std::unique_ptr<Logger>(new Logger());
    }
    qInstallMessageHandler(messageHandler);
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

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    std::string currentDatetime = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss").toStdString();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "%s [DEBUG]: %s (%s:%u, %s)\n", currentDatetime.data(), localMsg.constData(), file, context.line, function);
            break;
        case QtInfoMsg:
            fprintf(stderr, "%s [INFO]: %s (%s:%u, %s)\n", currentDatetime.data(), localMsg.constData(), file, context.line, function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "%s [WARNING]: %s (%s:%u, %s)\n", currentDatetime.data(), localMsg.constData(), file, context.line, function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "%s [CRITICAL]: %s (%s:%u, %s)\n", currentDatetime.data(), localMsg.constData(), file, context.line, function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "%s [FATAL]: %s (%s:%u, %s)\n", currentDatetime.data(), localMsg.constData(), file, context.line, function);
            break;
    }
}