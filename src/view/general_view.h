#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "equipment_status_view.h"
#include "automatic_control_tab_view.h"
#include "manual_power_control_view.h"
#include "auto_tunning_tab_view.h"
#include "chart_tab_view.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EquipmentStatusView equipmentView;
    AutomaticControlTabView automaticView;
    ManualPowerControlView manualPowerView;
    AutoTunningTabView autotunningView;
    ChartTabView chartView;
};

#endif // MAINWINDOW_H
