//
// Created by Martín García on 15/02/2020.
//

#ifndef TRABAJOPROFESIONAL_ZIEGLERS_NICHOLS_H
#define TRABAJOPROFESIONAL_ZIEGLERS_NICHOLS_H


#include "control_algorithm.h"

#define ZN_WINDOW_SIZE 10
#define INIT_POWER 10
#define DELTA_THRESHOLD 5

typedef enum {POWER_AT_10, POWER_AT_20, UNDEFINED} power_level_t;

class AutoTunningTabView;

class ZieglerNichols : public ControlAlgorithm {

public:
    explicit ZieglerNichols(AutoTunningTabView *, int initial_power,
                            int stationary_power, double cutoff_temp,
                            SerialPort *sp);

private:
    unsigned char process(std::shared_ptr<TemperatureReading> data) override;
    bool isTemperatureStable();
    void nextState();
    int min_power;
    int max_power;
    double cutoff_temp;
    power_level_t powerLevel = UNDEFINED;
    std::vector<float> tempBuffer;
    std::vector<std::shared_ptr<TemperatureReading>> stepResponse;
    uint64_t buffCounter = 0;
    AutoTunningTabView *autoTunningView;
};


#endif //TRABAJOPROFESIONAL_ZIEGLERS_NICHOLS_H
