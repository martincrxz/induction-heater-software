#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>

#include "logger/logger.h"
#include "app_config.h"
#include "exception.h"

const ApplicationConfig &ApplicationConfig::instance() {
    static ApplicationConfig instance(APP_CONFIG_FILEPATH);
    return instance;
}

ApplicationConfig::ApplicationConfig(std::string filepath): filepath(filepath) {
    bool fileExists = true;
    QFile jsonFile(filepath.c_str());
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        Logger::debug("Configuration file doesn't exist, creating it");
        fileExists = false;
    }

    jsonFile.close();

    if (!jsonFile.open(QIODevice::ReadWrite))
        throw Exception("Couldn't create/load json file %s", filepath.c_str());

    if (fileExists) {
        QByteArray saveData = jsonFile.readAll();
        json = QJsonObject(QJsonDocument::fromJson(saveData).object());
        checkConsistency();
    } else {
        loadDefaultValues();
    }
    Logger::info("Configuration loaded");
    connect(&this->automaticUpdateTimer, &QTimer::timeout, this, &ApplicationConfig::backupConfiguration);
    this->automaticUpdateTimer.start(60000); // backups cada 1 minuto
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
        throw Exception("There is no general configuration");
    QJsonObject generalConfig = json["general"].toObject();
    if (!generalConfig.contains("log_level") || !generalConfig["log_level"].isArray())
        throw Exception("Bad config format, general/log_level is not an array");
    if (!generalConfig.contains("window_size") || !generalConfig["window_size"].isDouble())
        throw Exception("Bad config format, general/window_size must be a number");
}

void ApplicationConfig::backupConfiguration() {
    QFile jsonFile(this->filepath.c_str());
    jsonFile.open(QIODevice::Truncate | QIODevice::ReadWrite);
    jsonFile.write(QJsonDocument(this->json).toJson());
    Logger::debug("Json config file updated");
}

ApplicationConfig::~ApplicationConfig()
{

}
