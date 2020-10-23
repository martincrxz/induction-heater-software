/**
 * Created by Federico Manuel Gomez Peter
 * Date: 17/10/20
 */

#ifndef TRABAJOPROFESIONAL_DUTEMULATOR_H
#define TRABAJOPROFESIONAL_DUTEMULATOR_H

#include "control/control_algorithm.h"
/**
 * Esta clase va a emular la curva de temperatura del horno.
 * Va a ser utilizada para testear los algoritmos de control.
 * recibirá en su llamado una potencia X, y devolverá una temperatura del DUT
 * en función de esto.
 */
class DutEmulator {
private:
    float previous_power{0.1};
    float current_temperature{25};
public:
    DutEmulator();
    DutEmulator(float init_temp, float init_power);
    ~DutEmulator();
    /**
     * Recibe la potencia que debe suministrar la aplicación, y en función de esto, devuelve una temperatura acorde
     * segun el modelo.
     */
    float process(float power);
};


#endif //TRABAJOPROFESIONAL_DUTEMULATOR_H
