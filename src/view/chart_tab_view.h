#ifndef CHART_TAB_VIEW_H
#define CHART_TAB_VIEW_H

#include <QPushButton>
#include <QtCharts/QChartView>
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

private slots:
    void onInitChartClicked();

private:
    Ui::ChartTabView *ui;
    QChartView chartView;
    QPushButton initChartButton{"Iniciar captura"};
};

#endif // CHART_TAB_VIEW_H
