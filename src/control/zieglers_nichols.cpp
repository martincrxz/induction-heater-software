//
// Created by Martín García on 15/02/2020.
//

#include "zieglers_nichols.h"
#include "../connection/protocol/set_power.h"

ZieglerNichols::ZieglerNichols(SerialPort *port) : ControlAlgorithm(0, port) {

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

    if(tempBuffer.size() >= ZN_WINDOW_SIZE)
        if(isTemperatureStable())
             nextState();

    if(powerLevel == POWER_AT_20)
        stepResponse.emplace_back(data->getData());

    float power = (powerLevel == POWER_AT_10) ? 10 : 20;

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
        // hacer algo con el stepResponse
        stop();
    }
}