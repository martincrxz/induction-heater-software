
/*
 * Created by Federico Manuel Gomez Peter
 * on 11/9/19.
 */

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>

class LoggerMessage {
protected:
    std::string msg;

public:
    LoggerMessage() = default;
    virtual ~LoggerMessage() = default;
    explicit LoggerMessage(std::string &message);
    /**
     * @brief Imprime el mensaje. Se aplica un polimorfismo para determinar
     * si se imprime como debug, info, warning o si es un mensaje de salida.
     */
    virtual void print() = 0;
    /**
     * @brief devuelve si es un mensaje de salida o no.
     * @return
     */
    virtual bool quit() = 0;
};


#endif // __MESSAGE_H__
