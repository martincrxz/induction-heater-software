
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */
#include <fstream>
#include <sstream>
#include "fuzzy_logic.h"
#include "MemberCandidate.h"
#include "OutputObject.h"

#define MIN(x, y) (x) < (y) ? (x) : (y)

FuzzyLogic::FuzzyLogic(float targetTemp, SerialPort *sp, uint8_t window_size): 
      ClassicPID(1, 0, 0, targetTemp, sp, window_size) {
    std::fstream file(RULES_FILEPATH, std::iostream::in );
    std::string line;
    // parseo el archivo, el csv debe ser una matriz de  Nx5 elementos
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::istringstream iss(line);
        std::string value;
        while (std::getline(iss, value, ',')) {
            row.push_back(std::move(value));
        }
        this->rules.push_back(std::move(row));
    }
    // TODO refactor this
    input_member_func.emplace_back(-2000,-2000, -200, -100, "NB");
    input_member_func.emplace_back(-200,-100 , -10, 0, "NS");
    input_member_func.emplace_back(-10, 0, 0, 10, "ZERO");
    input_member_func.emplace_back(0, 10, 100, 200, "PS");
    input_member_func.emplace_back(100, 200, 2000, 2000, "PB");

    output_member_func.emplace_back(-22, -15, -10, -3, "NEGATIVE");
    output_member_func.emplace_back(-7, -3, 3, 7, "ZERO");
    output_member_func.emplace_back(3, 10, 15, 22, "POSITIVE");
    
}

FuzzyLogic::~FuzzyLogic() {

}

unsigned char FuzzyLogic::process(std::shared_ptr<TemperatureReading> data) {
    this->updateParameters(data);
    return ClassicPID::process(data);
}

void FuzzyLogic::updateParameters(std::shared_ptr<TemperatureReading> data) {
    std::vector<MemberCandidate> errorCandidates;
    std::vector<MemberCandidate> derivativeErrorCandidates;

    for (auto &member: this->input_member_func) {
        float errorDegree = member.calculate(errorMean);
        float derivativeErrorDegree = member.calculate(derivativeError);
        if (errorDegree != 0)
            errorCandidates.emplace_back(errorDegree, member.getTag());
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
                    for (int i = 2, j = 0; i < rules.size(); i++)
                      outputs[j++].emplace(degree, rule[i]);

                }
            }
        }
    }

    this->Kp += outputs[0].calculate_delta(output_member_func);
    this->Kd += outputs[1].calculate_delta(output_member_func);
    this->Ki += outputs[2].calculate_delta(output_member_func);
}


