#include <iostream>
#include <QJsonObject>
#include <sstream>
#include "messages.h"

#include "fuzzy2x3.h"
#include "logger/logger.h"
#include "MemberCandidate.h"
#include "OutputObject.h"
#include "../configuration/app_config.h"

#define MIN(x, y) (x) < (y) ? (x) : (y)

Fuzzy2x3::Fuzzy2x3(float targetTemp,
        float kp,
        float kd,
        float ki,
        SerialPort *sp,
        const std::string &filepath,
        uint8_t window_size,
        float errorS,
        float errorDerivativeS,
        float kpS,
        float kiS,
        float kdS):
            FuzzyLogic(targetTemp, kp, kd, ki, sp, window_size, "fuzzy2x3"), errorSensitivity(errorS),
            errorDerivativeSensitivity(errorDerivativeS), kpSensitivity(kpS), kiSensitivity(kiS), kdSensitivity(kdS),
            initKp(kp), initKi(ki), initKd(kd){
    loadJson(filepath);
    printConf();
}

Fuzzy2x3::~Fuzzy2x3() {}

unsigned char Fuzzy2x3::process(std::shared_ptr<TemperatureReading> data) {
    this->updateParameters(data);
    return ClassicPID::process(data);
}

void Fuzzy2x3::updateParameters(std::shared_ptr<TemperatureReading> data) {
    std::vector<MemberCandidate> errorCandidates;
    std::vector<MemberCandidate> derivativeErrorCandidates;

    for (auto &member: this->errorMemberFunctions) {
        float errorDegree = member.calculate(errorMean / errorSensitivity);
        if (errorDegree != 0)
            errorCandidates.emplace_back(errorDegree, member.getTag());
    }

    for (auto &member: this->errorDerivativeMemberFunctions) {
        float derivativeErrorDegree = member.calculate(derivativeError / errorDerivativeSensitivity);
        if (derivativeErrorDegree != 0)
            derivativeErrorCandidates.emplace_back(derivativeErrorDegree, member.getTag());
    }

    std::uint32_t output_quantity = this->rules[1].size() - 2;
    std::vector<OutputObject> outputs(output_quantity);

    for (auto &rule: this->rules) {
        for (auto &ec: errorCandidates){
            for (auto &dec: derivativeErrorCandidates) {
                if (rule[0] == ec.tag && rule[1] == dec.tag) {
                    float degree = MIN(ec.degree, dec.degree);
                    for (unsigned int i = 2, j = 0; i < rule.size(); i++)
                      outputs[j++].emplace(degree, rule[i]);
                }
            }
        }
    }

    this->Kp = this->initKp + outputs[0].calculate_delta(kpOutputFunctions) * this->kpSensitivity;
    this->Kd = this->initKd + outputs[1].calculate_delta(kdOutputFunctions) * this->kdSensitivity;
    this->Ki = this->initKi + outputs[2].calculate_delta(kiOutputFunctions) * this->kiSensitivity;
}

void Fuzzy2x3::loadMemberFunctions(QJsonObject& document) {
    loadFunctions(errorMemberFunctions, document, "inputFunctions", "e");
    loadFunctions(errorDerivativeMemberFunctions, document, "inputFunctions", "de");
    loadFunctions(kpOutputFunctions, document, "outputFunctions", "dkp");
    loadFunctions(kiOutputFunctions, document, "outputFunctions", "dki");
    loadFunctions(kdOutputFunctions, document, "outputFunctions", "dkd");
}

void Fuzzy2x3::printConf() const {
    Logger::debug(FUZZY_CONFIG_HEADER_MSG);
    Logger::debug(FUZZY_2X3_CONFIG_RULES_HEADERS_MSG);
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

    Logger::debug(FUZZY_2X3_KP_FUNCTION_MSG);
    for (auto &function: kpOutputFunctions)
        function.print();

    Logger::debug(FUZZY_2X3_KD_OUT_FUNCT_MSG);
    for (auto &function: kdOutputFunctions)
        function.print();

    Logger::debug(FUZZY_2X3_KI_OUT_FUNCT_MSG);
    for (auto &function: kiOutputFunctions)
        function.print();
}
