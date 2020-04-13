#ifndef CHART_TAB_VIEW_H
#define CHART_TAB_VIEW_H

#include <QPushButton>
#include <QWidget>

#include "chart/chart_widget.h"
#include "../connection/protocol/temperature_reading.h"
#include "../connection/protocol/power_set_acknowledge.h"

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

private slots:
    void on_initChartButton_clicked();

private:
    Ui::ChartTabView *ui;
    ChartWidget *widget;
};

#endif // CHART_TAB_VIEW_H
