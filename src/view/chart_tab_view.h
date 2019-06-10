#ifndef CHART_TAB_VIEW_H
#define CHART_TAB_VIEW_H

#include <QWidget>
#include <QtCharts/QChartView>

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

private slots:
    void on_startChartButton_clicked();

private:
    Ui::ChartTabView *ui;
    QChart *chart;
};

#endif // CHART_TAB_VIEW_H
