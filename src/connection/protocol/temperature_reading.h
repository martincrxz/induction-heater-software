
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __TEMPERATURE_READING_H__
#define __TEMPERATURE_READING_H__

#include "micro_message.h"

class TemperatureReading: public MicroMessage {
private:
    float data;
public:
    TemperatureReading(QByteArray &buff);
    virtual ~TemperatureReading() = default;
    QByteArray serialize() override;
    float getData();
};


#endif // __TEMPERATURE_READING_H__
