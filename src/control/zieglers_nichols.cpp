//
// Created by Martín García on 15/02/2020.
//

#include "zieglers_nichols.h"
#include "../connection/protocol/set_power.h"
#include "../view/auto_tunning_tab_view.h"


ZieglerNichols::ZieglerNichols(AutoTunningTabView *view, int initial_power,
                            int stationary_power, double cutoff_temp,
                            SerialPort *port) : ControlAlgorithm(0, port, 0),
                            min_power(initial_power),
                            max_power(stationary_power),
                            cutoff_temp(cutoff_temp) {
    autoTunningView = view;
    std::shared_ptr<MicroMessage> msg(new SetPower(powerToTaps(10)));
    port->send(msg);
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
        this->autoTunningView->autotunningFailed("Error en el proceso: se llegó a la temperatura de corte");
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
        if(temp - avg > DELTA_THRESHOLD)
            return false;
    }
    return true;
}

void ZieglerNichols::nextState(){

    if(powerLevel == POWER_AT_10)
        powerLevel = POWER_AT_20;

    if(powerLevel == POWER_AT_20) {
        // Evito que se acepten nuevas muestras después de terminar este
        // procesamiento lento.
        this->keep_processing = false;
        autoTunningView->calculateParameters(stepResponse);
    }
}