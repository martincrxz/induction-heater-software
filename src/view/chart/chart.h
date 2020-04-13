/*
 * Created by Federico Manuel Gomez Peter
 * on 20/8/19.
 */

#ifndef __CHART_H__
#define __CHART_H__

#include <chrono.h>
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
#include <QtCore/QDateTime>
#include <QtCore/QMutex>
#include <cstdint>

#include "../../connection/protocol/temperature_reading.h"
#include "chart_conf.h"

QT_BEGIN_NAMESPACE
class QGestureEvent;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
class Chart :  public QChart {
    Q_OBJECT

public:
    Chart(ChartConfiguration *chartConfig, QGraphicsItem *parent = nullptr, 
            Qt::WindowFlags wFlags = nullptr);

    virtual ~Chart();
    void init();
    void stop();
    void dataAvailable(double y, unsigned int id = 1);
    void stopFollow();
    void startFollow();

protected:
    bool sceneEvent(QEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);
    void append(double x, double y, unsigned int id = 1);
    bool secondCurveEnabled{false};
    double y1min{0};
    double y1max{0};
    double y2min{0};
    double y2max{0};
    double xmin{0};
    double xmax{0};
    QSplineSeries series1;
    QSplineSeries series2;
    QDateTimeAxis xAxis;
    QValueAxis yAxis1;
    QValueAxis yAxis2;
    QMutex mutex;
    bool acceptData;
    Chrono chrono;
    bool auto_scroll_enabled{true};
};


#endif // __CHART_H__
