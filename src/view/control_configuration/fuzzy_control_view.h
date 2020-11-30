#ifndef FUZZY_CONTROL_VIEW_H
#define FUZZY_CONTROL_VIEW_H

#include <QString>
#include <QWidget>
#include "control_configuration.h"

#define FUZZY_2x3_NAME "Fuzzy logic"

namespace Ui {
class FuzzyControlView;
}

class FuzzyControlView : public ControlConfiguration
{
    Q_OBJECT

public:
    FuzzyControlView(QWidget *parent, SerialPort *sp);
    ~FuzzyControlView();
    bool validateInput() override;
    void instantiate() override;
    const char * getName() override;

public slots:
    /**
     * Recarga la lista de presets que viene en el json de la aplicación, y setea el preset pedido en <currentPreset>
     * para tener las variables de control de dicho preset.
     * @param currentPreset
     */
    void updateConfiguration();
private slots:
    void on_operationModeCombo_currentIndexChanged(int index);
    void on_openFile_clicked();
    void on_save_button_clicked();
    void on_constantsPresetCombo_currentIndexChanged(const QString &arg1);

private:
    Ui::FuzzyControlView *ui;
    QDoubleValidator *kValidator;
    QDoubleValidator *tempValidator;
    QDoubleValidator *sensitivityValidator;
    uint8_t current_index = 0;
    std::string selectedPresetName;
    bool validateInput(bool check_temp, bool pid_mode, bool check_file = true);
    void _updateConfiguration(const char* currentPreset);
    void loadPresetList(const char* currentPreset);
    void setPresetConfiguration(const char*currentPreset);
};

#endif // FUZZY_CONTROL_VIEW_H
