/*
 * Created by Federico Manuel Gomez Peter
 * on 20/8/19.
 */

#ifndef __CHART_H__
#define __CHART_H__

#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCore/QDateTime>
#include <QtCore/QMutex>
#include <chrono.h>
#include "../connection/protocol/temperature_reading.h"

QT_CHARTS_USE_NAMESPACE

class Chart :  public QChart {
    Q_OBJECT

public:
    explicit Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    virtual ~Chart();
    void init();
    void dataAvailable(TemperatureReading &msg);

private:
    void append(double x, double y);
    QLineSeries series;
    QDateTimeAxis xAxis;
    QValueAxis yAxis;
    QMutex mutex;
    bool acceptData;
    Chrono chrono;
};


#endif // __CHART_H__
