
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __TEMPERATURE_READING_H__
#define __TEMPERATURE_READING_H__


#include "micro_message.h"

class TemperatureReading: public MicroMessage {
public:
    TemperatureReading();
    virtual ~TemperatureReading() = default;
    QByteArray serialize() override;
};


#endif // __TEMPERATURE_READING_H__
