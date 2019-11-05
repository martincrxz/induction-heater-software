
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
    TemperatureReading(QByteArray &buff);
    virtual ~TemperatureReading() = default;
    float getData();
};


#endif // __TEMPERATURE_READING_H__
