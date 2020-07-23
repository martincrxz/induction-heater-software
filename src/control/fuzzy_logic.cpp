
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

FuzzyLogic::FuzzyLogic(float targetTemp, SerialPort *sp,
        const std::string &filepath, uint8_t window_size): 
	ClassicPID(1, 0, 0, targetTemp, sp, window_size) {
    loadJson(filepath);
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
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>
#include <iostream>
// TODO: odio QJsonObject. Su política de no romper nunca
// me genera la necesidad de chequear la existencia de
// cada atributo para poder tener mensajes de errores.
// Otras implementaciones como nlohmann-json son
// mucho mejores, pero no supe como compilarlas con qmake.
// (es necesario compilarlo con qmake para poder usar
// el asistente de instalación de qt. Para otra vida
// queda hacer un wrapper como la gente de QT que te haga
// los chequeos pertinentes)
void FuzzyLogic::loadJson(const std::string &filepath) {
    Logger::debug("loading json %s", filepath.c_str());
    QFile loadFile(filepath.c_str());

    if (!loadFile.open(QIODevice::ReadOnly))
        throw Exception("Couldn't load json file %s", filepath.c_str());

    QByteArray saveData = loadFile.readAll();

    QJsonObject document(QJsonDocument::fromJson(saveData).object());

    if (document["fuzzy2x3"].toObject()["rules"].isUndefined() ||
            !document["fuzzy2x3"].toObject()["rules"].isArray())
        throw Exception("array %s/rules is not an array", "fuzzy2x3");
    QJsonArray rules =  document["fuzzy2x3"].toObject()["rules"].toArray();

    for(int i = 0; i < rules.size(); i++){
        std::vector<std::string> row;
        if (rules[i].isUndefined() || !rules[i].isArray())
            throw Exception("Element %s/rules/%i is not an array", "fuzzy2x3", i);
        QJsonArray values = rules[i].toArray();
        for(int j = 0; j < values.size(); j++) {
            if (values[j].isUndefined() || !values[j].isString())
                throw Exception("Element %s/rules/%i/%i is not a string", "fuzzy2x3", i, j);
            row.push_back(values[j].toString().toStdString());
        }
    }

    loadFunctions(errorMemberFunctions, document, "inputFunctions", "e");
    loadFunctions(errorDerivativeMemberFunctions, document, "inputFunctions", "de");
    loadFunctions(kpOutputFunctions, document, "outputFunctions", "dkp");
    loadFunctions(kiOutputFunctions, document, "outputFunctions", "dki");
    loadFunctions(kdOutputFunctions, document, "outputFunctions", "dkd");
}

void FuzzyLogic::loadFunctions(std::vector<MemberFunction>& holder, QJsonObject &document,
        const std::string functionType, const std::string id){
    if (document["fuzzy2x3"].toObject()[functionType.c_str()].toObject()[id.c_str()].isUndefined() ||
            !document["fuzzy2x3"].toObject()[functionType.c_str()].toObject()[id.c_str()].isObject())
        throw Exception("Element %s/%s/%s is not an object", "fuzzy2x3", functionType.c_str(),
                        id.c_str());

    QJsonObject rules = document["fuzzy2x3"].toObject()[functionType.c_str()].toObject()[id.c_str()].toObject();

    for(QString &obj : rules.keys()) {
        if (!rules[obj].isArray())
            throw Exception("Element %s/%s/%s/%s should have 4 numbers", "fuzzy2x3", functionType.c_str(),
                        id.c_str(), obj.toStdString().c_str());
        holder.emplace_back(
                rules[obj].toArray()[0].toDouble(),
                rules[obj].toArray()[1].toDouble(),
                rules[obj].toArray()[2].toDouble(),
                rules[obj].toArray()[3].toDouble(),
                obj.toStdString());
        ;
    }
}


