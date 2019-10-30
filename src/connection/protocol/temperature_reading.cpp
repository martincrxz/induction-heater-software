
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "temperature_reading.h"
#include "apple_endian.h"
#include <iostream>
#include <QString>
#include <cmath>

TemperatureReading::TemperatureReading(QByteArray &buff):
                MicroMessage(TEMPERATURE_READING) {
    // Por protocolo, el mensaje enviará el dato de 32 bits como un entero
    // sin signo de 32 bits en formato big endian. Mediante uso de las
    // funciones estandar de C, se pasará el dato al endiannes de la máquina,
    // y si este dato fuera de otro tipo (un float) se lo castea a su dato
    // final
    uint32_t dataBits = be32toh(*((uint32_t *) &buff.data()[2]));
    float temp = ((dataBits >> 8) >> 5) & 0x3ffff;
    int sign = 1-2*((((dataBits >> 8) >> 5) & (1 << 18))>>18);
    this->data = (float) (sign * temp / 128.0);

    /*this->data = (float)(((uint8_t)buff[4] & 0xe0) / 4096.0);
    this->data += (float)(((uint8_t)buff[3]) / 16.0);
    this->data += (float)(((uint8_t)buff[2] & 0x7f) * 16.0);
    this->data *=  1.0 - 2.0*(((uint8_t)buff[2] & 0x80) >> 7);*/
}

QByteArray TemperatureReading::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = TEMPERATURE_READING;
    // Does not really make sense to implement this function for this type of message.
    return ret;
}

float TemperatureReading::getData() {
    return data;
}

