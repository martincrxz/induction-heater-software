
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */
#include <fstream>
#include <sstream>
#include "fuzzy_logic.h"

FuzzyLogic::FuzzyLogic(float targetTemp, SerialPort *sp): ClassicPID(1, 0, 0, targetTemp, sp) {
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
    input_member_func.emplace_back(-1, -1,-0.8,-0.6, "NB");
    input_member_func.emplace_back(-0.7,-0.5,-0.4,-0.2, "NS");
    input_member_func.emplace_back(-0.3,-0.1,0.1,0.3, "ZERO");
    input_member_func.emplace_back(0.2,0.4,0.5,0.7, "PS");
    input_member_func.emplace_back(0.6,0.8, 1, 1, "PB");

    output_member_func.emplace_back(-15, -15, -10, -3, "NEGATIVE");
    output_member_func.emplace_back(-7, -3, 3, 7, "ZERO");
    output_member_func.emplace_back(3, 10, 15, 15, "POSITIVE");
    
}

FuzzyLogic::~FuzzyLogic() {

}

unsigned char FuzzyLogic::process(std::shared_ptr<TemperatureReading> data) {
    this->updateParameters(data);
    return ClassicPID::process(data);
}

void FuzzyLogic::updateParameters(std::shared_ptr<TemperatureReading> data) {
    std::vector<std::tuple<float, const std::string &>> errorCandidates;
    std::vector<std::tuple<float, const std::string &>> derivativeErrorCandidates;

    for (auto &member: this->input_member_func) {
        float errorDegree = member.calculate(errorMean);
        float derivativeErrorDegree = member.calculate(derivativeError);
        if (errorDegree != 0)
            errorCandidates.emplace_back(errorDegree, member.getTag());
        if (derivativeErrorDegree != 0)
            derivativeErrorCandidates.emplace_back(derivativeErrorDegree, member.getTag());
    }
    // TODO quitar esta tupla de mierda
    for (auto &rule: this->rules) {
        for (auto &ec: errorCandidates){
            for (auto &dec: derivativeErrorCandidates) {
                if (rule[0] == std::get<1>(ec) && rule[1] == std::get<1>(dec)) {

                }
            }
        }
    }

}


