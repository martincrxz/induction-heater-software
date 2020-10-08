
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
#include <messages.h>

#include "fuzzy_logic.h"
#include "MemberCandidate.h"
#include "OutputObject.h"
#include "../configuration/app_config.h"

FuzzyLogic::FuzzyLogic(float targetTemp, SerialPort *sp,
        uint8_t window_size, std::string name): 
       ClassicPID(1, 0, 0, targetTemp, sp, window_size),
       mode(name) {}

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
    Logger::debug(LOADING_FILE_MSG, filepath.c_str());
    QFile loadFile(filepath.c_str());

    if (!loadFile.open(QIODevice::ReadOnly))
        throw Exception(FUZZY_LOGIC_ERROR_LOAD_FAILED_MSG, filepath.c_str());

    QByteArray saveData = loadFile.readAll();

    QJsonObject document(QJsonDocument::fromJson(saveData).object());

    if (document[mode.c_str()].isUndefined() || !document[mode.c_str()].isObject())
        throw Exception(FUZZY_LOGIC_FILE_BAD_FORMAT_ELEMNT_IS_NOT_OBJECT_MSG, mode.c_str());

    if (document[mode.c_str()].toObject()["rules"].isUndefined() ||
            !document[mode.c_str()].toObject()["rules"].isArray()) {
        std::string element = mode;
        element += "/rules";
        throw Exception(FUZZY_LOGIC_BAD_FORMAT_ELEMENT_IS_NOT_ARRAY_MSG, element.c_str());
    }
    QJsonArray rules =  document[mode.c_str()].toObject()["rules"].toArray();

    for(int i = 0; i < rules.size(); i++){
        std::vector<std::string> row;
        if (rules[i].isUndefined() || !rules[i].isArray()) {
            std::ostringstream element(mode);
            element << "/rules/" << i;
            throw Exception(FUZZY_LOGIC_BAD_FORMAT_ELEMENT_IS_NOT_ARRAY_MSG, element.str().c_str());
        }
        QJsonArray values = rules[i].toArray();
        for(int j = 0; j < values.size(); j++) {
            if (values[j].isUndefined() || !values[j].isString()) {
                std::ostringstream oss(mode);
                oss << "/rules/" << i << "/" << j;
                throw Exception(FUZZY_LOGIC_BAD_FORMAT_ELEMENT_IS_NOT_STRING, oss.str().c_str());
            }
            row.push_back(values[j].toString().toStdString());
        }
        this->rules.emplace_back(row);
    }

    loadMemberFunctions(document);
}

void FuzzyLogic::loadFunctions(std::vector<MemberFunction>& holder, QJsonObject &document,
        const std::string functionType, const std::string id){
    if (document[mode.c_str()].toObject()[functionType.c_str()].toObject()[id.c_str()].isUndefined() ||
            !document[mode.c_str()].toObject()[functionType.c_str()].toObject()[id.c_str()].isObject()) {
        std::ostringstream  oss(mode);
        oss << "/" << functionType << "/" << id;
        throw Exception(FUZZY_LOGIC_FILE_BAD_FORMAT_ELEMNT_IS_NOT_OBJECT_MSG, oss.str().c_str());
    }

    QJsonObject rules = document[mode.c_str()].toObject()[functionType.c_str()].toObject()[id.c_str()].toObject();

    for(QString &obj : rules.keys()) {
        if (!rules[obj].isArray()) {
            std::ostringstream oss(mode);
            oss << "/" << functionType << "/" << id << "/" << obj.toStdString();
            throw Exception(FUZZY_LOGIC_FILE_BAD_FORMAT_ELEMENT_SHOULD_HAVE_4_VALUES, oss.str().c_str());
        }
        holder.emplace_back(
                rules[obj].toArray()[0].toDouble(),
                rules[obj].toArray()[1].toDouble(),
                rules[obj].toArray()[2].toDouble(),
                rules[obj].toArray()[3].toDouble(),
                obj.toStdString());
    }
}
