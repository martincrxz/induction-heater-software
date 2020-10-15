#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <cstdint>

#include <messages.h>
#include "logger/logger.h"
#include "app_config.h"
#include "general_config.h"
#include "exception.h"

ApplicationConfig &ApplicationConfig::instance() {
    static ApplicationConfig instance(APP_CONFIG_FILEPATH);
    return instance;
}

ApplicationConfig::~ApplicationConfig() {}

ApplicationConfig::ApplicationConfig(std::string filepath): filepath(filepath) {
    levelName2value["debug"]    = DEBUG;
    levelName2value["info"]     = INFO;
    levelName2value["warning"]  = WARNING;
    levelName2value["critical"] = CRITICAL;
    levelName2value["fatal"]    = FATAL;

    bool fileExists = true;
    QFile jsonFile(filepath.c_str());
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        Logger::debug(APP_CONFIG_CONF_FILE_MISSING_MSG);
        fileExists = false;
    }

    jsonFile.close();

    if (!jsonFile.open(QIODevice::ReadWrite))
        throw Exception(APP_CONFIG_CONFIG_FILE_CREATE_ERROR_MSG, filepath.c_str());

    if (fileExists) {
        QByteArray saveData = jsonFile.readAll();
        json = QJsonObject(QJsonDocument::fromJson(saveData).object());
        checkConsistency();
    } else {
        loadDefaultValues();
    }

    QJsonArray log = json["general"].toObject()["log_level"].toArray();
    this->log_level_enabled = array2LogLevel(log);
    Logger::info(APP_CONFIG_CONF_FILE_LOADED_MSG);
}

uint8_t ApplicationConfig::getWindowSize() const {
    return json["general"].toObject()["window_size"].toInt();
}

uint8_t ApplicationConfig::getLogLevel() const {
    return log_level_enabled;
}

void ApplicationConfig::loadDefaultValues() {
    QJsonObject general_config;
    general_config.insert("window_size", QJsonValue(1));
    QJsonArray log_level;
    log_level.push_back(QJsonValue("debug"));
    log_level.push_back(QJsonValue("info"));
    log_level.push_back(QJsonValue("warning"));
    log_level.push_back(QJsonValue("critical"));
    log_level.push_back(QJsonValue("fatal"));
    general_config.insert("log_level", log_level);
    json.insert("general", general_config);

    QJsonObject control_config;
    QJsonObject classic_pid_control;
    classic_pid_control.insert("kp", QJsonValue(1));
    classic_pid_control.insert("kd", QJsonValue(1));
    classic_pid_control.insert("ki", QJsonValue(1));
    control_config.insert("classic_pid", classic_pid_control);
    json.insert("control_configuration", control_config);

    backupConfiguration();
}

void ApplicationConfig::checkConsistency() {
    // Debe tener si o si la configuración general,
    // sino, fallo
    if (!json.contains("general") || !json["general"].isObject())
        throw Exception(APP_CONFIG_GENERAL_CONF_MISSING_ERROR_MSG);
    QJsonObject generalConfig = json["general"].toObject();
    if (!generalConfig.contains("log_level") || !generalConfig["log_level"].isArray())
        throw Exception(FUZZY_LOGIC_BAD_FORMAT_ELEMENT_IS_NOT_ARRAY_MSG, "general/log_level");
    if (!generalConfig.contains("window_size") || !generalConfig["window_size"].isDouble())
        throw Exception(APP_CONFIG_BAD_FORMAT_WINDOW_SIZE_MUST_BE_NUMBER_MSG, "general/window_size");
}

void ApplicationConfig::backupConfiguration() {
    QFile jsonFile(this->filepath.c_str());
    jsonFile.open(QIODevice::Truncate | QIODevice::ReadWrite);
    jsonFile.write(QJsonDocument(this->json).toJson());
    Logger::debug(APP_CONFIG_CONFIG_FILE_UPDATED_MSG);
}

QJsonArray ApplicationConfig::loglevel2array(uint8_t log_level) {
    QJsonArray ret;
    for (auto &pair: this->levelName2value) {
        if (log_level & pair.second)
            ret.push_back(pair.first);
    }
    return ret;
}

uint8_t ApplicationConfig::array2LogLevel(const QJsonArray &array) {
    uint8_t ret = 0;
    for (auto value: array) {
        ret |= levelName2value.at(value.toString());
    }
    return ret;
}

void ApplicationConfig::updateConfig(const GeneralConfig &conf) {
    QJsonObject obj = this->json["general"].toObject();
    obj.insert("window_size", conf.window_size);
    obj.insert("log_level", loglevel2array(conf.log_level_enabled));
    this->log_level_enabled = conf.log_level_enabled;
    this->json.insert("general", obj);
    this->backupConfiguration();
    emit configChanged();
}
