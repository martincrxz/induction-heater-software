
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <memory>

#include "logger_worker.h"

class Logger {
private:
    /**
     * Responsable de loggear la info en el archivo de forma
     * thread-safe
     */
    LoggerWorker worker;
    /**
     * Se requiere instancia única del logger
     */
    static std::unique_ptr<Logger> instance;
    Logger();
public:
    /**
     * @brief Crea un archivo de log appendeando al filename la fecha de hoy
     * @param filename
     */
    static void init(const std::string &filename);
    /**
     * @brief crea un objeto LoggerInfo y se pushea en la queue.
     * @param msg
     */
    static void info(std::string msg);
    /**
     * @brief crea un objeto LoggerDebug y se pushea en la queue.
     * @param msg
     */
    static void debug(std::string msg);
    /**
     * @brief crea un objeto LoggerWarning y se pushea en la queue.
     * @param msg
     */
    static void warning(std::string msg);
    /**
     * @brief Liberará los recursos del worker de forma ordenada
     */
    virtual ~Logger();
};


#endif // __LOGGER_H__
