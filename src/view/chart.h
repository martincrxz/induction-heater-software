/*
 * Created by Federico Manuel Gomez Peter
 * on 20/8/19.
 */

#ifndef __CHART_H__
#define __CHART_H__

#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
#include <QtCore/QDateTime>
#include <QtCore/QMutex>
#include <chrono.h>
#include "../connection/protocol/temperature_reading.h"

QT_CHARTS_USE_NAMESPACE
struct ChartConfiguration {
    const char* yAxisName1;
    const char* yAxisType1;
    const char* yAxisName2;
    const char* yAxisType2;
    const char* xAxisName;
    const char* xAxisType;
    const char* title;
};

class Chart :  public QChart {
    Q_OBJECT

public:
    Chart(ChartConfiguration *chartConfig, QGraphicsItem *parent = nullptr, 
            Qt::WindowFlags wFlags = nullptr);

    virtual ~Chart();
    void init();
    void stop();
    void dataAvailable(double y, unsigned int id = 1);

private:
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
};


#endif // __CHART_H__
