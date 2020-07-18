
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */
#include <fstream>
#include <sstream>
#include "fuzzy_logic.h"
#include "MemberCandidate.h"
#include "OutputObject.h"
#include <rapidjson/istreamwrapper.h>
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
    std::fstream file(JSON_FILEPATH);
    Logger::debug("loading json %s", JSON_FILEPATH);
    if(!file.is_open()) {
        throw Exception("Couldn't load json file %s", JSON_FILEPATH);
    }
    rapidjson::IStreamWrapper isw(file);

    rapidjson::Document document;
    document.ParseStream(isw);

    for(auto &rule : document["fuzzy2x3"]["rules"].GetArray()){
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
        const std::string functionType, const std::string id){
    for(auto &obj : document["fuzzy2x3"][functionType.c_str()][id.c_str()].GetObject()){
        holder.emplace_back(
                obj.value.GetArray()[0].GetFloat(),
                obj.value.GetArray()[1].GetFloat(),
                obj.value.GetArray()[2].GetFloat(),
                obj.value.GetArray()[3].GetFloat(),
                obj.name.GetString());
    }
}


