
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */
#include <fstream>
#include <iostream>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <sstream>

#include "fuzzy_logic.h"
#include "MemberCandidate.h"
#include "OutputObject.h"

FuzzyLogic::FuzzyLogic(float targetTemp, SerialPort *sp,
        const std::string &filepath, uint8_t window_size, std::string name): 
       ClassicPID(1, 0, 0, targetTemp, sp, window_size),
       mode(name) {
    loadJson(filepath);
}

FuzzyLogic::~FuzzyLogic() {

}
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

    if (document[mode.c_str()].isUndefined() || !document[mode.c_str()].isObject())
        throw Exception("Element '%s' is not an object", mode.c_str());

    if (document[mode.c_str()].toObject()["rules"].isUndefined() ||
            !document[mode.c_str()].toObject()["rules"].isArray())
        throw Exception("Element '%s/rules' is not an array", mode.c_str());
    QJsonArray rules =  document[mode.c_str()].toObject()["rules"].toArray();

    for(int i = 0; i < rules.size(); i++){
        std::vector<std::string> row;
        if (rules[i].isUndefined() || !rules[i].isArray())
            throw Exception("Element '%s/rules/%i' is not an array", mode.c_str(), i);
        QJsonArray values = rules[i].toArray();
        for(int j = 0; j < values.size(); j++) {
            if (values[j].isUndefined() || !values[j].isString())
                throw Exception("Element '%s/rules/%i/%i' is not a string", mode.c_str(), i, j);
            row.push_back(values[j].toString().toStdString());
        }
        this->rules.emplace_back(row);
    }

    loadMemberFunctions(document);
}

void FuzzyLogic::loadFunctions(std::vector<MemberFunction>& holder, QJsonObject &document,
        const std::string functionType, const std::string id){
    if (document[mode.c_str()].toObject()[functionType.c_str()].toObject()[id.c_str()].isUndefined() ||
            !document[mode.c_str()].toObject()[functionType.c_str()].toObject()[id.c_str()].isObject())
        throw Exception("Element '%s/%s/%s' is not an object", mode.c_str(), functionType.c_str(),
                        id.c_str());

    QJsonObject rules = document[mode.c_str()].toObject()[functionType.c_str()].toObject()[id.c_str()].toObject();

    for(QString &obj : rules.keys()) {
        if (!rules[obj].isArray())
            throw Exception("Element '%s/%s/%s/%s' should have 4 numbers", mode.c_str(), functionType.c_str(),
                        id.c_str(), obj.toStdString().c_str());
        holder.emplace_back(
                rules[obj].toArray()[0].toDouble(),
                rules[obj].toArray()[1].toDouble(),
                rules[obj].toArray()[2].toDouble(),
                rules[obj].toArray()[3].toDouble(),
                obj.toStdString());
    }
}
