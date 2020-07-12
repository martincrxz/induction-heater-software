
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */
#include <fstream>
#include <sstream>
#include "fuzzy_logic.h"
#include "MemberCandidate.h"
#include "OutputObject.h"
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>

#define MIN(x, y) (x) < (y) ? (x) : (y)

FuzzyLogic::FuzzyLogic(float targetTemp, SerialPort *sp, uint8_t window_size): 
      ClassicPID(1, 0, 0, targetTemp, sp, window_size) {
    loadJson();
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
                    for (int i = 2, j = 0; i < rules.size(); i++)
                      outputs[j++].emplace(degree, rule[i]);
                }
            }
        }
    }

    this->Kp += outputs[0].calculate_delta(kpOutputFunctions);
    this->Kd += outputs[1].calculate_delta(kdOutputFunctions);
    this->Ki += outputs[2].calculate_delta(kiOutputFunctions);
}

void FuzzyLogic::loadJson() {
    FILE *fp = fopen(JSON_FILEPATH, "rb" );
    if(fp == NULL){
        Logger::warning("Could not correctly initialize fuzzy logic controller, input file error");
        return;
    }
    char readBuffer[JSON_BUFFER_SIZE];

    rapidjson::FileReadStream frs(fp, readBuffer, sizeof(readBuffer));

    rapidjson::Document document;
    document.ParseStream(frs);

    for(auto &rule : document["fuzzy3x2"]["rules"].GetArray()){
        std::vector<std::string> row;
        for(auto &value : rule.GetArray()){
            row.push_back(value.GetString());
        }
    }

    loadFunctions(errorMemberFunctions, document, "inputFunctions", "e");
    loadFunctions(errorDerivativeMemberFunctions, document, "inputFunctions", "de");
    loadFunctions(kpOutputFunctions, document, "outputFunctions", "dkp");
    loadFunctions(kiOutputFunctions, document, "outputFunctions", "dki");
    loadFunctions(kdOutputFunctions, document, "outputFunctions", "dkd");
}

void FuzzyLogic::loadFunctions(std::vector<MemberFunction>& holder, rapidjson::Document &document,
        const std::string &functionType, const std::string &id){
    for(auto &obj : document["fuzzy3x2"][functionType.c_str()][id.c_str()].GetObject()){
        holder.emplace_back(
                obj.value.GetArray()[0],
                obj.value.GetArray()[1],
                obj.value.GetArray()[2],
                obj.value.GetArray()[3],
                obj.name.GetString());
    }
}


