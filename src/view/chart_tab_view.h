#ifndef CHART_TAB_VIEW_H
#define CHART_TAB_VIEW_H

#include <QPushButton>
#include <QWidget>

#include "chart/chart_widget.h"
#include "../connection/protocol/temperature_reading.h"
#include "../connection/protocol/power_set_acknowledge.h"
#include "../connection/protocol/current_frequency_reading.h"
#include "../connection/protocol/current_RMS_reading.h"

namespace Ui {
class ChartTabView;
}

class ChartTabView : public QWidget
{
    Q_OBJECT

public:
    explicit ChartTabView(QWidget *parent = 0);
    virtual ~ChartTabView();
    void dataAvailable(TemperatureReading &temp);
    void dataAvailable(PowerSetAcknowledge &power);
    void dataAvailable(CurrentFrequencyReading &freq);
    void dataAvailable(CurrentRMSReading &current);

private slots:
    void on_initChartButton_clicked();

private:
    Ui::ChartTabView *ui;
    ChartWidget *widget;
};

#endif // CHART_TAB_VIEW_H
