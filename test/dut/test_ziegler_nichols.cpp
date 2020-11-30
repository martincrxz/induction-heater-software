//
// Created by fedemgp on 29/11/20.
//

#include "test_ziegler_nichols.h"

TestZieglerNichols::TestZieglerNichols(int initial_power, int stationary_power, double cutoff_temp):
        ZieglerNichols(nullptr, initial_power, stationary_power, cutoff_temp, nullptr) {}

power_level_t TestZieglerNichols::getState() const {
    return this->powerLevel;
}

bool TestZieglerNichols::isRunning() {
    return this->keep_processing;
}


