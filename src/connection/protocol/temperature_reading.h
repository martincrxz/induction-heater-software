
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __TEMPERATURE_READING_H__
#define __TEMPERATURE_READING_H__

#include "incoming_message.h"

class TemperatureReading: public IncomingMessage {
private:
    float data;
public:
	/**
	 * @brief			Transforma la tira de bytes recibido por el
	 *        	 		microcontrolador en un objeto DTO
	 * @param	buff 	Bytes enviados por el microcontrolador
	 */
    TemperatureReading(QByteArray &buff);
	/**
	 * @brief			Constructor usado para emular la recepción de una 
	 *          		temperatura por el micro.
	 * @param	temp 	Temperatura recibida (numero real)
	 */
    TemperatureReading(float temp);
    /**
     * @brief			Constructor copia
     */
    TemperatureReading(TemperatureReading &cpy);
    virtual ~TemperatureReading() = default;
    /**
     * @brief			Devuelve la tempeartura del DUT como un numero real
     * @return
     */
    float getData();
};


#endif // __TEMPERATURE_READING_H__
