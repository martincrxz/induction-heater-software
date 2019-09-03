
/*
 * Created by Federico Manuel Gomez Peter
 * on 3/9/19.
 */

#ifndef __LOGGER_WORKER_H__
#define __LOGGER_WORKER_H__

#include <string>
#include <QtCore/QThread>
#include <memory>
#include <mutex>
#include <stream.h>

/**
 * Se encargará de procesar todos los eventos de loggeo.
 *
 * Se ejecuta en un hilo aparte para darle alta
 * disponibilidad a los demás hilos, y que estos
 * no se queden bloqueados al escribir un archivo
 * (mas que nada los hilos de alto calculo matematico
 * como el controlador)
 *
 * A la vista del usuario no se usará, ya que ellos
 * interactuarán con el productor (Logger)
 */
class LoggerWorker: public  QThread{
    Q_OBJECT
public:
    /**
     * @brief Recibe el nombre del archivo donde se loggeará
     */
    LoggerWorker() = default;
    virtual ~LoggerWorker() override;
    /**
     * @brief Se encarga de terminar la ejecución ordenada
     * del worker
     */
    void stop();
    /**
     * @brief Escribe un mensaje de información
     * @param msg
     */
    void info(const std::string &msg);
private:
    IO::Stream<std::string> queue;
    bool keep_processing{true};
    /**
     * @brief Lanza el hilo de ejecución que toma elementos de a uno y
     * los imprime en la salida.
     */
    void run() override;
};


#endif // __LOGGER_WORKER_H__
