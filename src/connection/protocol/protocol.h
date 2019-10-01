
/*
 * Created by Federico Manuel Gomez Peter
 * on 21/9/19.
 */

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


#include <memory>
#include "micro_message.h"

#define ID_POSITION 1

class Protocol {
public:
    Protocol();
    /**
     * @brief Convierte el DTO en un arreglo de bytes listo para ser enviado
     * por el puerto serie.
     * @param objeto DTO
     * @return
     */
    QByteArray translate(MicroMessage *msg);
    /**
     * @brief Convierte la tira de bytes en un objeto DTO
     * @param buff
     * @return
     */
    std::shared_ptr<MicroMessage> translate(QByteArray &buff);
};


#endif // __PROTOCOL_H__
