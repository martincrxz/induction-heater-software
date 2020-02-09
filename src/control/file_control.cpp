/**
 * Created by Federico Manuel Gomez Peter
 * on 08/02/2020
 */
#include "file_control.h"

#include <logger/logger.h>
#include <sstream>
/**
 * La matriz steps se conforma de la siguiente forma
 * [
 *  [tiempo1, temp1, pot1],
 *  [tiempo2, temp2, pot2]
 *  ...
 *  [tiempoN, tempN, potN]
 * ]
 */
#define TIME_POSITION 0
#define TEMP_POSITION 1
#define POWER_POSITION 2

FileControl::FileControl(float kp, float ki, float kd,
                         ControlSteps &controlDirectives, SerialPort *sp):
		ClassicPID(kp, ki, kd, 0.0f, sp),
		steps(controlDirectives) {
}

void FileControl::reset(float newTargetTemp) {
	this->targetTemp = newTargetTemp;
	this->errorValues.clear();
	this->iteration = 0;
	this->chrono.tick();
}

FileControl::~FileControl() {

}
/**
 * Partiendo de la potencia inicial 100%, se calienta el horno a esta potencia,
 * a lazo abierto, hasta que se llegue a la temperatura de corte temp1 (que se
 * se encuentra en la matriz explicada previamente. Cuando se llega a esta
 * temperatura de corte, se aplica control clásico, donde la temperatura
 * objetivo es temp1, durante tiempo1 segundos. Una vez finalizado este tiempo,
 * se cambia la potencia a lazo abierto por pot1.
 *
 * Se continua calentando a lazo abierto, con la potencia pot1, hasta llegar a
 * la temperatura temp2, se controla durante tiempo2 segundos, y al finalizar
 * se pasa a pot2. Así sucesivamente, hasta llegar al final de los pasos.
 * @param data
 * @return
 */
unsigned char FileControl::process(std::shared_ptr<TemperatureReading> data) {
    if (this->step_count >= this->steps.size() ) {
        Logger::debug("Process finished");
        return ControlAlgorithm::powerToTaps(this->current_power);
    }
    if (this->state == OPEN_LOOP) {
        /*
         * En lazo abierto, debo chequear si superé la temperatura de corte.
         * Si lo hice, paso a modo lazo cerrado, y seteo el timer a cero. Si no,
         * se devuelve la potencia del paso (incialmente es 100%)
         */
        if (data->getData() >= this->steps[this->step_count][TEMP_POSITION]) {
            this->state = CLOSED_LOOP;
            Logger::debug("Changing to closed loop");
            this->reset(this->steps[this->step_count][TEMP_POSITION]);
            return ClassicPID::process(data);
        } else {
            //TODO, mejorar el logger, pasarle argumentos variables
            std::ostringstream oss;
            oss << "Open loop. Current power: " << this->current_power << "%";
            Logger::debug(oss.str());
            return ControlAlgorithm::powerToTaps(this->current_power);
        }
    } else {
        /*
         * En lazo cerrado, aplico el control clásico por tiempoN segundos. Al
         * finalizar cambio la potencia a devolver a lazo abierto
         */
        if (chrono.tack() >= this->steps[this->step_count][TIME_POSITION]) {
            this->state = OPEN_LOOP;
            Logger::debug("Changing to open loop");
            this->current_power = this->steps[this->step_count][POWER_POSITION];
            this->step_count++;
            return ControlAlgorithm::powerToTaps(this->current_power);
        } else {
            auto taps = ClassicPID::process(data);
            std::ostringstream oss;
            oss << "Closed loop. taps: " << taps;
            Logger::debug(oss.str());
            return taps;
        }
    }
}
