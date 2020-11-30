//
// Created by fedemgp on 29/11/20.
//

#include "test_ziegler_nichols.h"

TestZieglerNichols::TestZieglerNichols(int initial_power, int stationary_power, float cutoff_temp, float temp_sensitivity):
        ZieglerNichols(nullptr, initial_power, stationary_power, cutoff_temp, temp_sensitivity, nullptr) {}

power_level_t TestZieglerNichols::getState() const {
    return this->powerLevel;
}

bool TestZieglerNichols::isRunning() {
    return this->keep_processing;
}


