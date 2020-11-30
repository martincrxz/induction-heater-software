//
// Created by Martín García on 15/02/2020.
//

#ifndef TRABAJOPROFESIONAL_ZIEGLERS_NICHOLS_H
#define TRABAJOPROFESIONAL_ZIEGLERS_NICHOLS_H


#include "control_algorithm.h"

#define ZN_WINDOW_SIZE 20
#define INIT_POWER 10
#define DELTA_THRESHOLD 0.1

typedef enum {POWER_AT_10, POWER_AT_20, UNDEFINED} power_level_t;

class AutoTunningTabView;

class ZieglerNichols : public ControlAlgorithm {

public:
    explicit ZieglerNichols(AutoTunningTabView *, int initial_power,
                            int stationary_power, float cutoff_temp,
                            float temp_sensitivity,SerialPort *sp);
    unsigned char process(std::shared_ptr<TemperatureReading> data) override;

protected:
    power_level_t powerLevel = UNDEFINED;
    bool isTemperatureStable();
    void nextState();
    void calculateParameters(float &kp, float &kd, float &ki);

private:
    int min_power;
    int max_power;
    float cutoff_temp;
    float temp_sensitivity;
    std::vector<float> tempBuffer;
    std::vector<std::shared_ptr<TemperatureReading>> stepResponse;
    uint64_t buffCounter = 0;
    AutoTunningTabView *autoTunningView;
};


#endif //TRABAJOPROFESIONAL_ZIEGLERS_NICHOLS_H
