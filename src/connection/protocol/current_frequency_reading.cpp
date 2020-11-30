//
// Created by Martín García on 06/09/2020.
//

#include <QtEndian>
#include "current_frequency_reading.h"

CurrentFrequencyReading::CurrentFrequencyReading(QByteArray &buff) :
    IncomingMessage(CURRENT_FREQUENCY_READING) {
    // TODO: definir como se envian los datos y cambiar esto
    uint32_t dataBits = qFromBigEndian(*(uint32_t *) &buff.data()[2]);
    frequency = (float) CLOCK_FREQUENCY / dataBits;
}

CurrentFrequencyReading::CurrentFrequencyReading(float freq):
                    IncomingMessage(CURRENT_FREQUENCY_READING),
                    frequency(freq) {}

float CurrentFrequencyReading::getData() {
    return frequency;
}
