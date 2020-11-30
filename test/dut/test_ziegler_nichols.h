//
// Created by fedemgp on 29/11/20.
//

#ifndef TRABAJOPROFESIONAL_TEST_ZIEGLER_NICHOLS_H
#define TRABAJOPROFESIONAL_TEST_ZIEGLER_NICHOLS_H

#include <control/zieglers_nichols.h>

class TestZieglerNichols: public ZieglerNichols {
public:
    TestZieglerNichols(int initial_power, int stationary_power, float cutoff_temp, float temp_sensitivity);
    power_level_t getState() const;
    bool isRunning();
};


#endif //TRABAJOPROFESIONAL_TEST_ZIEGLER_NICHOLS_H
