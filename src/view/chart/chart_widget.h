#ifndef CHART_WIDGET_H
#define CHART_WIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>

#include "chart.h"
#include "chart_view.h"
#include "../../connection/protocol/power_set_acknowledge.h"
#include "../../connection/protocol/current_frequency_reading.h"
#include "../../connection/protocol/current_RMS_reading.h"

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
    void dataAvailable(CurrentFrequencyReading &freq);
    void dataAvailable(CurrentRMSReading &current);
    void init();

private slots:
    void on_stopFollowButton_clicked();

    void on_enableFollowButton_clicked();

    void on_fitViewButton_clicked();

    void on_saveButton_clicked();

    void on_settingsButton_clicked();

private:
	/**
	 * @brief Reimplementación del evento de cierre de ventana. Se agregará
	 * lógica para guardar o no la captura realizada de los datos.
	 */
	void closeEvent(QCloseEvent *event) override;
    Ui::ChartWidget *ui;
    Chart *temp_power_chart;
    Chart *current_chart;
    ChartView *temp_chart_view;
    ChartView *current_chart_view;
};

#endif // CHART_WIDGET_H
