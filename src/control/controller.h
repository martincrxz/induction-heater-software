//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_CONTROLLER_H
#define TRABAJOPROFESIONAL_CONTROLLER_H

#include <array>
#include <QObject>

#define BUFFER_SIZE 12

class Controller : public QObject{
    Q_OBJECT
private:
    std::array<float, BUFFER_SIZE> buffer;

public slots:
    void receiveNewData(float);

signals:
    void newDataReceived();
};


#endif //TRABAJOPROFESIONAL_CONTROLLER_H
