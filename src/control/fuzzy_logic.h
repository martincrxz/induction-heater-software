
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */

#ifndef __FUZZY_LOGIC_H__
#define __FUZZY_LOGIC_H__

#include <vector>
#include <string>

#include "classic_pid.h"
#include "MemberFunction.h"

/**
 * DISCLAIMER:  Control que aplica la logica difusa. Es una clase abstracta
 *              que solamente sabe como leer el JSON de configuración para
 *              cargar los parámetros de la implementación particular de cada
 *              uno (porque al variar las entradas y salidas de control
 *              te cambia la acción de control. En el modo 2x3, controlás
 *              las constantes del control clásico en función del error
 *              y la derivada del error, mientras que en modo
 *              3x1, controlás directamente la potencia del horno en función
 *              del error, la derivada del error y su integral, sin aplicar
 *              control clásico en el medio).
 *
 *              Para aquel que le toque leer este código, me disculpo de antemano.
 *              Es un código horrible, si, queda pendiente para otra vida
 *              hacer un refactor como la gente (se podrían haber ejecutado
 *              ambos modos en esta misma clase). Decidí no hacerlo porque
 *              hubiera afeado mas el código, aunque igual quedó un código feo.
 *              Si llego (y si las ganas me dejan), trataré de testear
 *              unitariamente este código. Si no llego a hacerlo, que dios
 *              se apiade de quien tenga que extender esto.
 */
class FuzzyLogic: public ClassicPID {
public:
    FuzzyLogic(float targetTemp, SerialPort *sp, const std::string &filepath,
                uint8_t window_size, std::string name);
    virtual ~FuzzyLogic() override;

protected:
    std::string mode;
    std::vector<std::vector<std::string>> rules;
    /**
     * Actualiza los parametros kp kd y ki en función del error derivativo
     * y el error de la medicion.
     */
    void loadJson(const std::string &filepath);
    /**
     * Función abstracta para que internamente se llamen N veces a loadFunction
     * en función de las member function que tenga cada modo
     */
    virtual void loadMemberFunctions(QJsonObject& document) = 0;
    void loadFunctions(std::vector<MemberFunction>& holder, QJsonObject &document,
            const std::string functionType, const std::string id);
    /**
     * @brief  Imprime la configuración del control (loggeando en debug)
     */
    virtual void printConf() const = 0;
};


#endif // __FUZZY_LOGIC_H__
