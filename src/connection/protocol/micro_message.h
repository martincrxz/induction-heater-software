
/*
 * Created by Federico Manuel Gomez Peter
 * on 22/9/19.
 */

#ifndef __MICRO_MESSAGE_H__
#define __MICRO_MESSAGE_H__

#include <QtCore/QByteArray>

typedef enum {PING_ID = 0x01, PONG_ID} message_id;

#define MESSAGE_SEPARATOR 0x7E

class MicroMessage {
private:
    message_id id;
public:
    explicit MicroMessage(message_id id);
    virtual ~MicroMessage() = default;
    /**
     * @brief devuelve el id de la clase (cada clase hija
     * tendrá un id distinto.
     * @return
     */
    message_id getId();
    /**
     * @brief función polimorfica que transforma el DTO en una tira de
     * bytes para ser enviado al puerto serie.
     * @return
     */
    virtual QByteArray serialize() = 0;
};


#endif // __MICRO_MESSAGE_H__
