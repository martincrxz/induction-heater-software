//
// Created by Martín García on 06/09/2020.
//

#include <QtEndian>
#include <cmath>
#include "current_RMS_reading.h"

CurrentRMSReading::CurrentRMSReading(QByteArray &buff) :
    IncomingMessage(CURRENT_RMS_READING) {
    // TODO: definir como se envian los datos y cambiar esto
    uint32_t dataBits = qFromBigEndian(*(uint32_t *) &buff.data()[2]);
    memcpy(&current, &dataBits, sizeof(current));
    current = std::sqrt(current);
}
CurrentRMSReading::CurrentRMSReading(float current): IncomingMessage(CURRENT_RMS_READING),
                                                     current(current) {}

float CurrentRMSReading::getData() {
    return current;
}
