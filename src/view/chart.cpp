/*
 * Created by Federico Manuel Gomez Peter
 * on 20/8/19.
 */

#include "chart.h"

#include <QtCharts/QAbstractAxis>
#include <QtCore/QDateTime>
#define TIME_CHART_MAX_RANGE 30
#define TIME_REJECT_DATA 100

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
        QChart(QChart::ChartTypeCartesian, parent, wFlags) {
    QPen green(Qt::blue);
    green.setWidth(3);
    this->series.setPen(green);

    this->addSeries(&this->series);
    this->legend()->hide();

    this->setTitle("Mediciones del horno");

    this->xAxis.setTickCount(10);
    this->xAxis.setFormat("HH:mm:ss");
    this->xAxis.setTitleText("Tiempo");

    this->yAxis.setLabelFormat("%i");
    this->yAxis.setTitleText("Temperatura (°C)");

    this->addAxis(&this->xAxis, Qt::AlignBottom);
    QDateTime now = QDateTime::currentDateTime();
    this->xAxis.setRange(now, now.addSecs(TIME_CHART_MAX_RANGE) );
    this->series.attachAxis(&this->xAxis);
    this->addAxis(&this->yAxis, Qt::AlignLeft);
    this->yAxis.setRange(0, 5);
    this->series.attachAxis(&this->yAxis);

}

Chart::~Chart() {

}

void Chart::append(double x, double y) {
    this->series.append(x, y);
    if (x > this->xAxis.max().toMSecsSinceEpoch()) {
        this->scroll(25, 0);
    }

    if (y > this->yAxis.max()) {
        this->yAxis.setRange(0, y + 10);
    } else if ( y < this->yAxis.min()) {
        this->yAxis.setRange(y -10, this->yAxis.max());
    }
}

void Chart::init() {
    QMutexLocker lock(&this->mutex);
    this->acceptData = true;
}

void Chart::dataAvailable(TemperatureReading &msg) {
    QMutexLocker lock(&this->mutex);
    if (acceptData && chrono.tack() > TIME_REJECT_DATA) {
        this->append(chrono.now(), msg.getData());
        chrono.tick();
    }
}

