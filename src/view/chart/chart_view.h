#ifndef __CHART_VIEW_H__
#define __CHART_VIEW_H__

#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>

#include "chart.h"

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView {
public:
    ChartView(Chart *chart, QWidget *parent = 0);
    void stopFollow();
    void startFollwo();
protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    bool m_isTouching;
    Chart *chart;
};

#endif
