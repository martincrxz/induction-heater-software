//
// Created by Martín García on 15/02/2020.
//

#include "messages.h"
#include "zieglers_nichols.h"
#include "../connection/protocol/set_power.h"
#include "../view/auto_tunning_tab_view.h"

ZieglerNichols::ZieglerNichols(AutoTunningTabView *view, int initial_power,
                            int stationary_power, float cutoff_temp,
                            float temp_sensitivity, SerialPort *port) : 
                            ControlAlgorithm(0, port, 0),
                            min_power(initial_power),
                            max_power(stationary_power),
                            cutoff_temp(cutoff_temp),
                            temp_sensitivity(temp_sensitivity) {
    autoTunningView = view;
    if (port) {
        std::shared_ptr<MicroMessage> msg(new SetPower(powerToTaps(10)));
        port->send(msg);
    }
    powerLevel = POWER_AT_10;
}

unsigned char ZieglerNichols::process(std::shared_ptr<TemperatureReading> data) {

    if(tempBuffer.size() < ZN_WINDOW_SIZE)
        tempBuffer.emplace_back(data->getData());
    else
        tempBuffer[buffCounter % ZN_WINDOW_SIZE] = data->getData();
    buffCounter++;
    if (data->getData() > cutoff_temp) {
        this->keep_processing = false;
        // forma mas rápida de deshabilitar el emit.
        if (this->autoTunningView)
            this->autoTunningView->autotunningFailed(ZN_ERROR_LIMIT_TEMP_REACHED_MSG);
        return powerToTaps(10);
    }

    if(tempBuffer.size() >= ZN_WINDOW_SIZE)
        if(isTemperatureStable())
             nextState();
    
    if(powerLevel == POWER_AT_20)
        stepResponse.emplace_back(data);

    float power = (powerLevel == POWER_AT_10) ? min_power : max_power;

    return powerToTaps(power);
}

bool ZieglerNichols::isTemperatureStable(){
    float avg = std::accumulate(tempBuffer.begin(), tempBuffer.end(), 0);
    avg /= ZN_WINDOW_SIZE;
    for(auto temp : tempBuffer){
        if(temp - avg > temp_sensitivity)
            return false;
    }
    return true;
}

void ZieglerNichols::nextState(){

    if(powerLevel == POWER_AT_10) {
        powerLevel = POWER_AT_20;
        this->tempBuffer.clear();
        this->buffCounter = 0;
    } else if (powerLevel == POWER_AT_20) {
        // Evito que se acepten nuevas muestras después de terminar este
        // procesamiento lento.
        this->keep_processing = false;
        float kp, kd, ki;
        kd = kp = ki = 0;
        this->calculateParameters(kp, kd, ki);
        if (this->autoTunningView)
            autoTunningView->znCalculated(kp, kd, ki);
    }
}

void ZieglerNichols::calculateParameters(float &kp, float &kd, float &ki) {
    /*
     * Primero, obtengo el máximo de la señal promediando las ultimas
     * muestras estables de la respuesta al escalon
     */
    std::size_t begin = stepResponse.size() - ZN_WINDOW_SIZE - 1;
    float minTemp = stepResponse[0]->getData();
    float maxTemp = 0;
    /**
     * Se sabe que las ultimas ZN_WINDOW_SIZE muestras son todas similares
     * ya que es condición necesaria para que se termine a recepción de
     * muestras.
     */
    for (std::size_t i = begin; i < stepResponse.size(); i++) {
        maxTemp += stepResponse[i]->getData();
    }
    maxTemp /= ZN_WINDOW_SIZE;
    /**
     * Una vez obtenido el maximo, se va a buscar los tiempos en los que se
     * llegue al 10% de la señal, y al 90% de la señal.
     *
     * Esto resulta en una aproximación al calculo de los parámetros por ziegler
     * nichols. Se decidió tomar esta aproximación y no calcular los parámetros
     * por definición debido al costo y la complejidad de buscar el punto de
     * inflexión de la señal (punto donde la derivada segunda valga cero) en
     * forma discreta.
     *
     * TODO: revisar la unidad de los tiempos, ahora están en milis, pero eso
     * puede hacer que las constantes sean muy chicas (tendrían unidad de
     * porcentaje/milis
     */
    std::uint64_t t10 = 0, t90 = 0;
    std::uint64_t t0 = stepResponse[0]->getTimestamp();
    float temp10 = minTemp + (maxTemp - minTemp) * 0.1f;
    float temp90 = minTemp + (maxTemp - minTemp) * 0.9f;
    bool t10Found = false;
    for (auto p : stepResponse) {
        if (p->getData() >= temp10 && !t10Found) {
            t10Found = true;
            t10 = p->getTimestamp() - t0;
        }

        if (p->getData() >= temp90)
            t90 = p->getTimestamp() - t0;
    }
    /*
     * Una vez obtenido t10 y t90, y sabiendo a priori la variación de la señal
     * del horno (10%) y la variación de la señal de temperatura
     * (maxTemp - minTemp), se procede a calcular los parámetros de control,
     * que se guardarán en un archivo para su posterior uso.
     *
     * kp= 1.2 * k0
     * ki = 0.60*Ko/T10
     * kd = 0.60*Ko*T110
     */
    float k0 = 10.0f * t90 / ((maxTemp - minTemp) * t10);
    kp = 1.2f * k0;         // [kp] = % / °C
    ki = 0.6f * k0/t10;     // [ki] = % / (ms * °C)
    kd = 0.6f * k0 * t10;   // [kd] = % * ms / °C
}