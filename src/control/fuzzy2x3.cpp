#include <iostream>
#include <QJsonObject>
#include <sstream>

#include "fuzzy2x3.h"
#include "logger/logger.h"
#include "MemberCandidate.h"
#include "OutputObject.h"

#define MIN(x, y) (x) < (y) ? (x) : (y)

Fuzzy2x3::Fuzzy2x3(float targetTemp, SerialPort *sp,
                const std::string &filepath, uint8_t window_size): 
            FuzzyLogic(targetTemp, sp, window_size, "fuzzy2x3") {
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
        float errorDegree = member.calculate(errorMean);
        if (errorDegree != 0)
            errorCandidates.emplace_back(errorDegree, member.getTag());
    }

    for (auto &member: this->errorDerivativeMemberFunctions) {
        float derivativeErrorDegree = member.calculate(derivativeError);
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
                    for (unsigned int i = 2, j = 0; i < rules.size(); i++)
                      outputs[j++].emplace(degree, rule[i]);
                }
            }
        }
    }

    this->Kp += outputs[0].calculate_delta(kpOutputFunctions);
    this->Kd += outputs[1].calculate_delta(kdOutputFunctions);
    this->Ki += outputs[2].calculate_delta(kiOutputFunctions);
}


void Fuzzy2x3::loadMemberFunctions(QJsonObject& document) {
    loadFunctions(errorMemberFunctions, document, "inputFunctions", "e");
    loadFunctions(errorDerivativeMemberFunctions, document, "inputFunctions", "de");
    loadFunctions(kpOutputFunctions, document, "outputFunctions", "dkp");
    loadFunctions(kiOutputFunctions, document, "outputFunctions", "dki");
    loadFunctions(kdOutputFunctions, document, "outputFunctions", "dkd");
}

void Fuzzy2x3::printConf() const {
    Logger::debug("FuzzyLogic configuration");
    Logger::debug("Rules:");
    Logger::debug("[e,   de,   dkp,   dki,   dkd]");
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
    Logger::debug("Error member functions configuration");
    for (auto &function: errorMemberFunctions)
        function.print();

    Logger::debug("Derivative error member functions configuration");
    for (auto &function: errorDerivativeMemberFunctions)
        function.print();

    Logger::debug("Kp output functions configuration");
    for (auto &function: kpOutputFunctions)
        function.print();

    Logger::debug("Kd output functions configuration");
    for (auto &function: kdOutputFunctions)
        function.print();

    Logger::debug("Ki output functions configuration");
    for (auto &function: kiOutputFunctions)
        function.print();
}
