#ifndef CHART_WIDGET_H
#define CHART_WIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>

#include "chart.h"
#include "chart_view.h"
#include "../../connection/protocol/power_set_acknowledge.h"

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

private slots:
    void on_stopFollowButton_clicked();

    void on_enableFollowButton_clicked();

    void on_fitViewButton_clicked();

private:
	/**
	 * @brief Reimplementación del evento de cierre de ventana. Se agregará
	 * lógica para guardar o no la captura realizada de los datos.
	 */
	void closeEvent(QCloseEvent *event) override;
    Ui::ChartWidget *ui;
    Chart *chart;
    ChartView *chartView;
};

#endif // CHART_WIDGET_H
