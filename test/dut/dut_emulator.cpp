/**
 * Created by Federico Manuel Gomez Peter
 * Date: 17/10/20
 */
#include <gtest/gtest.h>

#include "dut_emulator.h"
#include "csv_writter.h"
#include "control/control_algorithm.h"
#include "control/classic_pid.h"
#include "control/fuzzy2x3.h"
#include "control/fuzzy3x1.h"
#include "control/zieglers_nichols.h"


// Temperatura a partir de la cual la pendiente de temperatura cambia por efecto curie
#define CURIE_TEMPERATURE 700
#define SLOPE_UNDER_CURIE 0.001
#define SLOPE_OVER_CURIE 0.0002
#define INERTIA 0.5
#define AMOUNT_OF_ITERATIONS 10000

DutEmulator::DutEmulator() {}
DutEmulator::DutEmulator(float init_temp, float init_power): previous_power(init_power), current_temperature(init_temp) {}
DutEmulator::~DutEmulator() {}

float DutEmulator::process(float power) {
    float temp;
    float simulated_power;
    // Simulo el avance de la potencia para que no parezca que cambia de forma instantanea
    simulated_power = (power + INERTIA * (this->previous_power - power));
    // Este polinomio da la temperatura maxima dada una potencia,
    // we podria usar cualquier otra funcion
    temp = 1111.1 * simulated_power * simulated_power + 972.22 * simulated_power - 83.333;
    this->previous_power = simulated_power;
    // Ajusto la evolución de la temperatura en función si pasé el punto de curie o no.
    temp = temp - this->current_temperature;
    if (current_temperature < CURIE_TEMPERATURE)
        temp *= SLOPE_UNDER_CURIE;
    else
        temp *= SLOPE_OVER_CURIE;
    temp += this->current_temperature;
    this->current_temperature = temp;
    // TODO agregar ruido de medicion
    // n = 5*randn(1); % simula un ruido de medicion
    // ver https://en.cppreference.com/w/cpp/numeric/random/normal_distribution
    return temp;
}

TEST(ControlAlgorithms, DutReturns25DegreesIfThePowerIs10Percent) {
    DutEmulator dut;
    EXPECT_EQ(dut.process(0.1), 25.00);
}

TEST(ControlAlgorithms, DutWillStabilizeAt900DegreesWithProportionalControl) {
    DutEmulator dut;
    CsvWritter csv("DutWillStabilizeAt900DegreesWithProportionalControl.csv");
    ClassicPID pid(10, 0, 0, 900, NULL, 1);
    float temp = dut.process(0.1);
    for (int i = 0; i < AMOUNT_OF_ITERATIONS; i++) {
        float power = ControlAlgorithm::tapsToPower(pid._process(temp))/100;
        csv.writeData(power, temp);
         temp = dut.process(power);
    }
    ASSERT_TRUE(temp >= 890 && temp <= 910);
}

TEST(ControlAlgorithms, DutWillStabilizeAt900DegreesWithPIDControl) {
    DutEmulator dut;
    ClassicPID pid(3, 0.0005, 1, 900, NULL, 1);
    CsvWritter csv("DutWillStabilizeAt900DegreesWithPIDControl.csv");
    float temp = dut.process(0.1);
    for (int i = 0; i < AMOUNT_OF_ITERATIONS; i++) {
        float power = ControlAlgorithm::tapsToPower(pid._process(temp))/100;
        csv.writeData(power, temp);
         temp = dut.process(power);
    }
    ASSERT_TRUE(temp >= 890 && temp <= 910);
}

TEST(ControlAlgorithms, DutWithHighTemperature) {
    DutEmulator dut(2000, 1);
    ClassicPID pid(1, 0.01, 0.1, 900, NULL, 1);
    CsvWritter csv("DutWithHighTemperature.csv");
    float temp = dut.process(1);
    for (int i = 0; i < AMOUNT_OF_ITERATIONS; i++) {
        float power = ControlAlgorithm::tapsToPower(pid._process(temp))/100;
        csv.writeData(power, temp);
         temp = dut.process(power);
    }
    ASSERT_TRUE(temp >= 890 && temp <= 910);
}

TEST(ControlAlgorithms, Fuzzy2x3Control) {
    DutEmulator dut;
    std::string filepath("./fuzzy/fuzzy2x3.json");
    Fuzzy2x3 fuzzy(900, 0.1, 0.1, 0.1, NULL, filepath, 1);
    CsvWritter csv("Fuzzy2x3Control.csv");
    float temp = dut.process(0.1);
    for (int i = 0; i < AMOUNT_OF_ITERATIONS; i++) {
        float power = ControlAlgorithm::tapsToPower(fuzzy._process(temp))/100;
        csv.writeData(power, temp);
         temp = dut.process(power);
    }
    ASSERT_TRUE(temp >= 890 && temp <= 910);
}

TEST(ControlAlgorithms, Fuzzy3x1Control) {
    DutEmulator dut;
    std::string filepath("./fuzzy/fuzzy3x1.json");
    Fuzzy3x1 fuzzy(900, NULL, filepath, 1);
    CsvWritter csv("Fuzzy3x1Control.csv");
    float temp = dut.process(0.1);
    for (int i = 0; i < AMOUNT_OF_ITERATIONS; i++) {
        float power = ControlAlgorithm::tapsToPower(fuzzy._process(temp))/100;
        csv.writeData(power, temp);
         temp = dut.process(power);
    }
    ASSERT_TRUE(temp >= 890 && temp <= 910);
}
