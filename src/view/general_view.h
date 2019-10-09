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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void shutdownMessage(std::shared_ptr<MicroMessage> msg);
public slots:
    void on_shutdownButton_clicked();
private:
    Ui::MainWindow *ui;
    SerialPort *port;
    EquipmentStatusView *equipmentView;
    AutomaticControlTabView *automaticView;
    ManualPowerControlView *manualPowerView;
    AutoTunningTabView *autotunningView;
    ChartTabView *chartView;
};

#endif // MAINWINDOW_H
