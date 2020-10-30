#ifndef FROM_FILE_CONTROL_VIEW_H
#define FROM_FILE_CONTROL_VIEW_H

#define FROM_FILE_CONTROL_NAME "Desde archivo"

#include <cstdint>
#include <QWidget>
#include <QDoubleValidator>
#include <vector>

#include "control_configuration.h"

namespace Ui {
class FromFileControlView;
}

class FromFileControlView: public ControlConfiguration
{
    Q_OBJECT

public:
    explicit FromFileControlView(QWidget *parent, SerialPort *sp);
    ~FromFileControlView();
    bool validateInput() override;
    void instantiate() override;
    const char * getName() override;

public slots:
    void updateConfiguration();
private slots:
    void on_openFile_clicked();
    void on_saveButton_clicked();

    void on_constantsPresetCombo_currentIndexChanged(const QString &arg1);

private:
    Ui::FromFileControlView *ui;
    std::vector<std::vector<std::uint32_t>> controlDirectives;
    QDoubleValidator *kValidator;
    std::string selectedPresetName;
    void parseFile();
    void _updateConfiguration(const char* currentPreset);
    void loadPresetList(const char* currentPreset);
    void setPresetConfiguration(const char*currentPreset);
};

#endif // FROM_FILE_CONTROL_VIEW_H
