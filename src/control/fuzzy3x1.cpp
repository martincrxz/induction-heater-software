#include <iostream>
#include <QJsonObject>
#include <sstream>
#include "messages.h"

#include "fuzzy3x1.h"
#include "logger/logger.h"
#include "MemberCandidate.h"
#include "OutputObject.h"
#include "../configuration/app_config.h"

#define MIN(x, y, z) (x) < (y) ? (((x) < (z)) ? (x) : (z)): (((y) < (z)) ? (y) : (z))

Fuzzy3x1::Fuzzy3x1(float targetTemp, SerialPort *sp, const std::string &filepath,
                    uint8_t window_size):
            FuzzyLogic(targetTemp, sp, window_size, "fuzzy3x1") {
    loadJson(filepath);
    printConf();
}

Fuzzy3x1::~Fuzzy3x1() {}

unsigned char Fuzzy3x1::process(std::shared_ptr<TemperatureReading> data) {
    // Llamo al process del control clásico para actualizar las variables de
    // entrada (la media del error, el error derivativo y el error integral)
    // Silencio la salida del control PID porque no me intersa.
    // Puede parecer innecesario, pero con eso evito código duplicado.
    ClassicPID::process(data);
    updateParameters(data);
    return ControlAlgorithm::powerToTaps(power);
}

void Fuzzy3x1::updateParameters(std::shared_ptr<TemperatureReading> data) {
    std::vector<MemberCandidate> errorCandidates;
    std::vector<MemberCandidate> derivativeErrorCandidates;
    std::vector<MemberCandidate> integralErrorCandidates;

    for (auto &member: this->errorMemberFunctions) {
        float errorDegree = member.calculate(errorMean);
        if (errorDegree != 0)
            errorCandidates.emplace_back(errorDegree, member.getTag());
    }

    for (auto &member: this->errorDerivativeMemberFunctions) {
        float derivativeErrorDegree = member.calculate(derivativeError);
        if (derivativeErrorDegree != 0)
            derivativeErrorCandidates.emplace_back(derivativeErrorDegree, member.getTag());
    }

    for (auto &member: this->errorIntegralMemberFunctions) {
        float integralErrorDegree = member.calculate(integralError);
        if (integralErrorDegree != 0)
            integralErrorCandidates.emplace_back(integralErrorDegree, member.getTag());
    }

    OutputObject output;
    // TODO: refactor, evitar busqueda lineal.
    for (auto &rule: this->rules) {
        for (auto &ec: errorCandidates) {
            for (auto &dec: derivativeErrorCandidates) {
                for (auto &iec: integralErrorCandidates) {
                    if (rule[0] == ec.tag && rule[1] == dec.tag && rule[2] == iec.tag) {
                        float degree = MIN(ec.degree, dec.degree, iec.degree);
                        output.emplace(degree, rule[3]);
                    }
                }
            }
        }
    }
    this->power += output.calculate_delta(powerOutputFunctions);
}

void Fuzzy3x1::loadMemberFunctions(QJsonObject& document) {
    loadFunctions(errorMemberFunctions, document, "inputFunctions", "e");
    loadFunctions(errorDerivativeMemberFunctions, document, "inputFunctions", "de");
    loadFunctions(errorIntegralMemberFunctions, document, "inputFunctions", "ie");
    loadFunctions(powerOutputFunctions, document, "outputFunctions", "p");
}

void Fuzzy3x1::printConf() const {
    Logger::debug(FUZZY_CONFIG_HEADER_MSG);
    Logger::debug(FUZZY_3X1_RULES_CONF_HEADER_MSG);
    for (auto &row: this->rules) {
        std::ostringstream oss;
        oss << "[";
        for (unsigned int i = 0; i < row.size();) {
            oss << row[i];
            if (++i < row.size())
                oss << ", ";
        }
        oss << "]";
        Logger::debug(oss.str().c_str());
    }
    Logger::debug(FUZZY_ERROR_MEMBER_FUNCT_HEADER_MSG);
    for (auto &function: errorMemberFunctions)
        function.print();

    Logger::debug(FUZZY_DERIVATIVE_ERROR_HEADER_MSG);
    for (auto &function: errorDerivativeMemberFunctions)
        function.print();

    Logger::debug(FUZZY_INTEGRA_ERROR_MEMBER_FUNCT_HEADER_MSG);
    for (auto &function: errorIntegralMemberFunctions)
        function.print();

    Logger::debug(FUZZY_OUTPUT_POWER_HEADER_MSG);
    for (auto &function: powerOutputFunctions)
        function.print();

}