#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "equipment_status_view.h"
#include "automatic_control_tab_view.h"
#include "manual_power_control_view.h"
#include "auto_tunning_tab_view.h"
#include "chart_tab_view.h"
#include "../connection/protocol/micro_message.h"
#include "../connection/serialport.h"
#include "dialog/general_config_dialog.h"

typedef enum {MANUAL, AUTOMATIC} control_type_t;

namespace Ui {
class MainWindow;
}
#define STEP_SIZE 1000
#define POWER_STEP_SIZE 500
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isControlActivated();

public slots:
    void on_shutdownButton_clicked();
    void onTemperatureDataArrived(std::shared_ptr<MicroMessage> msg);
    void onColdJunctionDataArrived(std::shared_ptr<MicroMessage> msg);
    void onCurrentFrequencyArrived(std::shared_ptr<MicroMessage> msg);
    void onCurrentRMSArrived(std::shared_ptr<MicroMessage> msg);
    void thermocoupleChange(int);
    void onPowerSetAckArrived(std::shared_ptr<MicroMessage> msg);
    void onSetManualControl(int index);
    void onStatusChanged();
    void onSerialPortConnected();
    void onSerialPortDisconnected();
    void onManualPowerSet();
    void onAutomaticPowerSet();
    void onControlTypeChanged();
    void onZNCalculated(float, float, float);
    /**
     * @brief Imprime un mensaje de error o de exito al querer enviar
     * un mensaje de seteo de conrol manual
     * @param str
     * @param mode
     */
    void on_messagePrint(const char *str, unsigned char mode, bool reset);

private slots:
    void on_actionConfiguration_triggered();

private:
    Ui::MainWindow *ui;
    SerialPort *port;
    EquipmentStatusView *equipmentView;
    AutomaticControlTabView *automaticView;
    ManualPowerControlView *manualPowerView;
    AutoTunningTabView *autotunningView;
    ChartTabView *chartView;
    QTimer *resetLabelTimer;
    bool usbOk = true;
    bool thermocoupleOk = true;
    control_type_t controlType = MANUAL;
    // Testing
    QTimer *testTimer;
    Chrono chrono;
    std::uint8_t power_value{0};
    std::uint64_t  temp_step{STEP_SIZE};
    std::uint64_t  power_step{POWER_STEP_SIZE};
    float amplitude{2};
    GeneralConfigDialog confDialog;
    void injectData();

    /**
     * @brief deja el mensaje de warning con texto vacio
     */
    void resetLabel();
    void enableAutomaticControlButtons(bool enable);
    void resync_microcontroller();
    void deactivateProcess();
public slots:
    void configChanged();
};

#endif // MAINWINDOW_H
