//
// Created by Martín García on 06/09/2020.
//

#ifndef TRABAJOPROFESIONAL_CURRENTFREQUENCYREADING_H
#define TRABAJOPROFESIONAL_CURRENTFREQUENCYREADING_H


#include "incoming_message.h"

class CurrentFrequencyReading : public IncomingMessage{
private:
    float data;
public:
    CurrentFrequencyReading(QByteArray&);
    ~CurrentFrequencyReading()= default;
    float getData();
};


#endif //TRABAJOPROFESIONAL_CURRENTFREQUENCYREADING_H
