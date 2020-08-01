#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include <QObject>
#include <QJsonObject>
#include <QFile>
#include <QTimer>
#include <string>

#define APP_CONFIG_FILEPATH "app_configuration.json"

class ApplicationConfig: public QObject {
    Q_OBJECT
private:
    std::string filepath;
    QJsonObject json;
    QTimer automaticUpdateTimer;

    ApplicationConfig(std::string filepath);
    void loadDefaultValues();
    void checkConsistency();
    void backupConfiguration();
public:
    ~ApplicationConfig();
    static const ApplicationConfig  &instance();
};

#endif
