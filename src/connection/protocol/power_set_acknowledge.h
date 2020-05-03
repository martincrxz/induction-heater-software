
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __POWER_SET_ACKNOWLEDGE_H__
#define __POWER_SET_ACKNOWLEDGE_H__

#define MINIMUM_TAP 0   // potencia maxima (100%)
#define MAXIMUM_TAP 127 // potencia minima (0%)

#include <cstdint>

#include "incoming_message.h"

class PowerSetAcknowledge: public IncomingMessage {
private:
    std::uint8_t data;
public:
	/**
	 * @brief	Parsea los bytes que recibe del micro por puerto serie
	 *        	para armar el DTO
	 */
    explicit PowerSetAcknowledge(QByteArray &);
    /**
     * @brief			Usado en modo testing, se pasa una potencia (entero
     *          		del 1 al 100) para simular el mensaje del micro
     * @param  power 	entero del 1 al 100
     */
    explicit PowerSetAcknowledge(std::uint8_t power);
    virtual ~PowerSetAcknowledge() = default;
    /**
     * @brief			Devuelve la potencia como un numero real del 1 al 100
     * @return 
     */
    float getPower();
};


#endif // __POWER_SET_ACKNOWLEDGE_H__
