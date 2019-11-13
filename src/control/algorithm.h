//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_ALGORITHM_H
#define TRABAJOPROFESIONAL_ALGORITHM_H

#include <QObject>
#include <memory>
#include "../connection/protocol/micro_message.h"

class Algorithm : public QObject{
    Q_OBJECT

private:

public slots:
    virtual void calculatePower() = 0;
// senal abstracta... uhmm no lo se rick.
//signals:
//    virtual void powerCalculated(std::shared_ptr<MicroMessage>) = 0;
};


#endif //TRABAJOPROFESIONAL_ALGORITHM_H
