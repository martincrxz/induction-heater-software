#include <iostream>
#include <QJsonObject>
#include <sstream>
#include "messages.h"

#include "fuzzy2x1.h"
#include "logger/logger.h"
#include "MemberCandidate.h"
#include "OutputObject.h"
#include "../configuration/app_config.h"

#define MIN(x, y) (x) < (y) ? (x) : (y)

Fuzzy2x1::Fuzzy2x1(float targetTemp,
        SerialPort *sp,
        const std::string &filepath,
        uint8_t window_size,
        float errorS,
        float errorDerivativeS,
        float outputS):
            FuzzyLogic(targetTemp, 0, 0, 0, sp, window_size, "fuzzy3x1"),
            errorSensitivity(errorS),
            errorDerivativeSensitivity(errorDerivativeS),
            outputSensitivity(outputS){
    loadJson(filepath);
    printConf();
}

Fuzzy2x1::~Fuzzy2x1() {}

unsigned char Fuzzy2x1::process(std::shared_ptr<TemperatureReading> data) {
    // Llamo al process del control clásico para actualizar las variables de
    // entrada (la media del error, el error derivativo y el error integral)
    // Silencio la salida del control PID porque no me intersa.
    // Puede parecer innecesario, pero con eso evito código duplicado.
    ClassicPID::process(data);
    updateParameters(data);
    return ControlAlgorithm::powerToTaps(power);
}

void Fuzzy2x1::updateParameters(std::shared_ptr<TemperatureReading> data) {
    std::vector<MemberCandidate> errorCandidates;
    std::vector<MemberCandidate> derivativeErrorCandidates;

    for (auto &member: this->errorMemberFunctions) {
        float errorDegree = member.calculate(errorMean/errorSensitivity);
        if (errorDegree != 0)
            errorCandidates.emplace_back(errorDegree, member.getTag());
    }

    for (auto &member: this->errorDerivativeMemberFunctions) {
        float derivativeErrorDegree = member.calculate(derivativeError/errorDerivativeSensitivity);
        if (derivativeErrorDegree != 0)
            derivativeErrorCandidates.emplace_back(derivativeErrorDegree, member.getTag());
    }

    OutputObject output;
    for (auto &rule: this->rules) {
        for (auto &ec: errorCandidates) {
            for (auto &dec: derivativeErrorCandidates) {
                if (rule[0] == ec.tag && rule[1] == dec.tag) {
                    float degree = MIN(ec.degree, dec.degree);
                    output.emplace(degree, rule[2]);
                }
            }
        }
    }
    this->power += output.calculate_delta(powerOutputFunctions) * outputSensitivity;
    this->power = (this->power > 100) ? 100 : this->power;
    this->power = (this->power < 10) ? 10 : this->power;
}

void Fuzzy2x1::loadMemberFunctions(QJsonObject& document) {
    loadFunctions(errorMemberFunctions, document, "inputFunctions", "e");
    loadFunctions(errorDerivativeMemberFunctions, document, "inputFunctions", "de");
    loadFunctions(powerOutputFunctions, document, "outputFunctions", "p");
}

void Fuzzy2x1::printConf() const {
    Logger::debug(FUZZY_CONFIG_HEADER_MSG);
    Logger::debug(FUZZY_2X1_RULES_CONF_HEADER_MSG);
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


    Logger::debug(FUZZY_OUTPUT_POWER_HEADER_MSG);
    for (auto &function: powerOutputFunctions)
        function.print();

}