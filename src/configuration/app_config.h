#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include <QObject>
#include <QJsonObject>
#include <QFile>
#include <QTimer>
#include <string>
#include <map>

#include "general_config.h"
#define APP_CONFIG_FILEPATH "app_configuration.json"

class ApplicationConfig: public QObject {
    Q_OBJECT
private:
    std::string filepath;
    QJsonObject json;
    std::map<QString, uint8_t> levelName2value;
    uint8_t log_level_enabled;

    ApplicationConfig(std::string filepath);
    void loadDefaultValues();
    void checkConsistency();
    void backupConfiguration();
    QJsonArray loglevel2array(uint8_t log_level);
    uint8_t array2LogLevel(const QJsonArray &array);
public:
    ~ApplicationConfig();
    static ApplicationConfig  &instance();
    uint8_t getWindowSize() const;
    uint8_t getLogLevel() const;
    double getCurrentAdjustmentCoefficient() const;
    void updateConfig(const GeneralConfig &conf);

signals:
    void configChanged();
};

#endif
