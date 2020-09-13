//
// Created by Martín García on 06/09/2020.
//

#ifndef TRABAJOPROFESIONAL_CURRENTRMSREADING_H
#define TRABAJOPROFESIONAL_CURRENTRMSREADING_H


#include "incoming_message.h"

class CurrentRMSReading : public IncomingMessage{
private:
    float current;
public:
    CurrentRMSReading(QByteArray&);
    CurrentRMSReading(float current);
    ~CurrentRMSReading() = default;
    float getData();
};


#endif //TRABAJOPROFESIONAL_CURRENTRMSREADING_H
