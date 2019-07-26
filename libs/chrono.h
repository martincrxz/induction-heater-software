/*
 * Created by Federico Manuel Gomez Peter
 * on 25/06/19.
 */

#ifndef __CHRONO_H__
#define __CHRONO_H__


#include <chrono>
#include <ostream>

#define CHRONO_PRECISION 2
#define CHRONO_UNIT "ms"

class Chrono {
 public:
    Chrono();
    ~Chrono() = default;
    /**
     * Pisa el tiempo de start con la hora actual
     */
    void tick();
    /**
     * Devuelve el tiempo parcial desde el ultimo tick
     * @return tiempo en milisegundos
     */
    double tack();
    /**
     * Retorna el tiempo actual en milisegundos
     */
    double now();
 private:
    std::chrono::high_resolution_clock::time_point start;
};

/**
 * Imprime el tiempo actual formateado en el flujo de salida 
 * que se le pase
 * @param os
 * @return
 */
std::ostream& operator<<(std::ostream &os, Chrono &chrono);


#endif  // __CHRONO_H__
