
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <cstdarg>
#include <memory>

#include "logger_worker.h"

#define FILE_NAME "application.log"

class Logger {
private:
    /**
     * Responsable de loggear la info en el archivo de forma
     * thread-safe
     */
    LoggerWorker worker;
    Logger();
    static Logger& instance();
public:
    /**
     * @brief Crea un archivo de log para appendear informacion
     */
    static void init();
    /**
     * @brief crea un objeto LoggerInfo y se pushea en la queue.
     * @param formato estilo printf
     * @param argumentos variables
     */
    static void info(const char * fmt, ...);
    /**
     * @brief crea un objeto LoggerDebug y se pushea en la queue.
     * @param formato estilo printf
     * @param argumentos variables
     */
    static void debug(const char * fmt, ...);
    /**
     * @brief crea un objeto LoggerWarning y se pushea en la queue.
     * @param formato estilo printf
     * @param argumentos variables
     */
    static void warning(const char * fmt, ...);
    /**
     * @brief crea un objeto LoggerCritical y se pushea a la queue
     * @param formato estilo printf
     * @param argumentos variables
     */
    static void critical(const char * fmt, ...);
    /**
     * @brief Liberará los recursos del worker de forma ordenada
     */
    virtual ~Logger();

private:
    /**
     * @brief Dado una lista de argumentos variables y un formato del estilo
     * printf, se crea un string formateado con todas las variables.
     *
     * Ejemplo:
     * fmt: "Hola %s"
     * args: ["mundo!"]
     * msg: "Hola mundo!"
     * @param fmt  string con formato estilo printf 
     * @param args una lista de argumentos variables
     * @param msg  mensaje final formateado.
     */
    static void parseString(const char *fmt, va_list &args, std::string &msg);
};


#endif // __LOGGER_H__
