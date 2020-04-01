#ifndef CHART_WIDGET_H
#define CHART_WIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>

#include "chart.h"
#include "../connection/protocol/power_set_acknowledge.h"

namespace Ui {
class ChartWidget;
}

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = 0);
    ~ChartWidget();
    void dataAvailable(TemperatureReading &temp);
    void dataAvailable(PowerSetAcknowledge &power);
    void init();

private:
	/**
	 * @brief Reimplementación del evento de cierre de ventana. Se agregará
	 * lógica para guardar o no la captura realizada de los datos.
	 */
	void closeEvent(QCloseEvent *event) override;
    Ui::ChartWidget *ui;
    Chart *chart;
    QChartView chartView;
};

#endif // CHART_WIDGET_H
