#ifndef CHART_TAB_VIEW_H
#define CHART_TAB_VIEW_H

#include <QPushButton>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QWidget>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class ChartTabView;
}

class ChartTabView : public QWidget
{
    Q_OBJECT

public:
    explicit ChartTabView(QWidget *parent = 0);
    ~ChartTabView();

protected:
    void timerEvent(QTimerEvent *) override;

private slots:
    void onInitChartClicked();

private:
    Ui::ChartTabView *ui;
    QChartView chartView;
    QChart chart;
    QLineSeries series;
    QDateTimeAxis xAxis;
    QValueAxis yAxis;
    QPushButton initChartButton{"Iniciar captura"};
};

#endif // CHART_TAB_VIEW_H
