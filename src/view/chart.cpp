/*
 * Created by Federico Manuel Gomez Peter
 * on 20/8/19.
 */

#include "chart.h"

#include <QtCharts/QAbstractAxis>
#include <QtCore/QDateTime>
#define TIME_CHART_MAX_RANGE 30
#define TIME_REJECT_DATA 100

Chart::Chart(ChartConfiguration *config, QGraphicsItem *parent, 
            Qt::WindowFlags wFlags) :
        QChart(QChart::ChartTypeCartesian, parent, wFlags) {
    QPen pen(Qt::blue);
    pen.setWidth(3);
    this->series1.setPen(pen);

    this->addSeries(&this->series1);
    this->legend()->hide();

    this->setTitle(config->title);

    this->xAxis.setTickCount(10);
    this->xAxis.setFormat(config->xAxisType);
    this->xAxis.setTitleText(config->xAxisName);

    this->yAxis1.setLabelFormat(config->yAxisType1);
    this->yAxis1.setTitleText(config->yAxisName1);


    this->addAxis(&this->xAxis, Qt::AlignBottom);
    QDateTime now = QDateTime::currentDateTime();
    this->xAxis.setRange(now, now.addSecs(TIME_CHART_MAX_RANGE) );
    this->series1.attachAxis(&this->xAxis);

    this->addAxis(&this->yAxis1, Qt::AlignLeft);
    this->yAxis1.setRange(0, 5);
    this->series1.attachAxis(&this->yAxis1);

    if (config->yAxisName2 != nullptr) {
        QPen pen2(Qt::green);
        pen2.setWidth(3);
        this->series2.setPen(pen2);

        this->addSeries(&this->series2);
        this->legend()->hide();

        this->secondCurveEnabled = true;    
        this->yAxis2.setLabelFormat(config->yAxisType2);
        this->yAxis2.setTitleText(config->yAxisName2);
    
        this->addAxis(&this->yAxis2, Qt::AlignRight);
        this->yAxis2.setRange(0,50);
    }


}

Chart::~Chart() {
    this->acceptData = false;
}

void Chart::append(double x, double y, unsigned int id) {
    if (id == 1) {
        this->series1.append(x, y);
        if (x > this->xAxis.max().toMSecsSinceEpoch()) {
            this->scroll(25, 0);
        }

        if (y > this->yAxis1.max()) {
            this->yAxis1.setRange(0, y + 10);
        } else if ( y < this->yAxis1.min()) {
            this->yAxis1.setRange(y -10, this->yAxis1.max());
        }
    } else {
        if (this->secondCurveEnabled) {
            this->series2.append(x, y);
            if (x > this->xAxis.max().toMSecsSinceEpoch()) {
                this->scroll(25, 0);
            }

            if (y > this->yAxis2.max()) {
                this->yAxis2.setRange(0, y + 10);
            } else if ( y < this->yAxis2.min()) {
                this->yAxis2.setRange(y -10, this->yAxis2.max());
            }
        }
    }
}

void Chart::init() {
    QMutexLocker lock(&this->mutex);
    this->acceptData = true;
}

void Chart::dataAvailable(double y, unsigned int id) {
    QMutexLocker lock(&this->mutex);
    if (acceptData && chrono.tack() > TIME_REJECT_DATA) {
        this->append(chrono.now(), y, id);
        chrono.tick();
    }
}

