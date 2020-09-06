//
// Created by Martín García on 06/09/2020.
//

#include <QtEndian>
#include "current_RMS_reading.h"

CurrentRMSReading::CurrentRMSReading(QByteArray &buff) :
    IncomingMessage(CURRENT_RMS_READING) {
    // TODO: definir como se envian los datos y cambiar esto
    uint32_t dataBits = qFromBigEndian(*(uint32_t *) &buff.data()[2]);
    data = (float) dataBits;
}

float CurrentRMSReading::getData() {
    return data;
}
