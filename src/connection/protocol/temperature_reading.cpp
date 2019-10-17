
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#include "temperature_reading.h"
#include "apple_endian.h"

TemperatureReading::TemperatureReading(QByteArray &buff):
                MicroMessage(TEMPERATURE_READING) {
    // Por protocolo, el mensaje enviará el dato de 32 bits como un entero
    // sin signo de 32 bits en formato little endian. Mediante uso de las
    // funciones estandar de C, se pasará el dato al endiannes de la máquina,
    // y si este dato fuera de otro tipo (un float) se lo castea a su dato
    // final
    uint32_t aux = le32toh(*((uint32_t *) &buff.data()[2]));
    this->data = aux;
}

QByteArray TemperatureReading::serialize() {
    QByteArray ret(8, 0x00);
    ret[0] = MESSAGE_SEPARATOR;
    ret[1] = TEMPERATURE_READING;
    uint32_t aux = htole32(this->data);
    memcpy(&ret.data()[2], (char *)&aux, 4);
    return ret;
}

float TemperatureReading::getData() {
    return data;
}

