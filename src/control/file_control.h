/**
 * Created by Federico Manuel Gomez Peter
 * on 08/02/2020
 */

#ifndef __FILE_CONTROL_H__
#define __FILE_CONTROL_H__

#include <cstdint>
#include <chrono.h>

#include "classic_pid.h"
#include "control_algorithm.h"

typedef std::vector<std::vector<std::uint32_t>> ControlSteps;
typedef enum{OPEN_LOOP, CLOSED_LOOP} ControlState;

class FileControl: public ClassicPID
{
public:
	FileControl(float kp, float ki, float kd, ControlSteps &controlDirectives,
                SerialPort *sp);
	~FileControl();
    /**
     *	Dado una temperatura nueva, se deja calentar a lazo abierto hasta que
     *	se alcance la temperatura objetivo. Cuando esto sucede, se controla
     *	mediante control clasico un tiempo x, dado por una lista de pasos
     *	(steps). Una vez pasados esos segundos, se procede a la siguiente etapa,
     *	donde se deja calentar a lazo abierto hasta llegar a la siguiente
     *	temperatura de control, y se repite los pasos descriptos hasta
     *	que se terminen los pasos. El valor de retorno es la
     *	cantidad de vueltas que debe dar el potenciómetro electrónico.
     *
     *	TODO: está conceptualmente mal que devuelva la cantidad de vueltas.
     *	La aplicación no debe saber como el horno controla la potencia a
     *	aplicar. Esta transformación debe hacerla el micro.
     */
    virtual unsigned char process(std::shared_ptr<TemperatureReading> data) override;
protected:
		void reset(float newTargetTemp);
		
private:
	ControlSteps &steps;
	std::uint32_t  step_count{0};
	/**
	 * Estado del control por archivo, cuando está a lazo abierto, se devuelve
	 * siempre la potencia que diga el step[step_count][2]. En lazo cerrado
	 * se aplicará control clásico, reutilizando el método del padre.
	 */
    ControlState state{OPEN_LOOP};
    float current_power{100.0f};
    Chrono chrono;

};

#endif