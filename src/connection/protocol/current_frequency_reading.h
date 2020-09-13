//
// Created by Martín García on 06/09/2020.
//

#ifndef TRABAJOPROFESIONAL_CURRENTFREQUENCYREADING_H
#define TRABAJOPROFESIONAL_CURRENTFREQUENCYREADING_H


#include "incoming_message.h"

// TODO: tal vez habría que hacer variable esto en función
// de la configuración del micro.
#define SAMPLE_RATE 1e6

class CurrentFrequencyReading : public IncomingMessage{
private:
    float frequency;
public:
    CurrentFrequencyReading(QByteArray&);
    /**
     * @brief       Constructor  para testear el producto.
     * 
     * @param freq
     */
    CurrentFrequencyReading(float freq);
    ~CurrentFrequencyReading()= default;
    float getData();
};


#endif //TRABAJOPROFESIONAL_CURRENTFREQUENCYREADING_H
