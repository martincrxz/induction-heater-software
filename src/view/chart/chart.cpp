/*
 * Created by Federico Manuel Gomez Peter
 * on 20/8/19.
 */

#include "chart.h"

#include <fstream>
#include <QtCore/QString>
#include <logger/logger.h>
#include <QtCharts/QAbstractAxis>
#include <QtCore/QDateTime>
#include <QtWidgets/QGesture>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include "messages.h"

#define TIME_REJECT_DATA 100

QColor Chart::getNextColor() {
    static std::uint8_t idx = 0;
    static std::vector<QColor> availableColors;
    if (availableColors.size() == 0) {
        availableColors.emplace_back(Qt::blue);
        availableColors.emplace_back(Qt::green);
        availableColors.emplace_back(Qt::black);
        availableColors.emplace_back(Qt::red);
    }
    return availableColors[++idx % availableColors.size()];
}

Chart::Chart(ChartConfiguration *config, QGraphicsItem *parent, 
            Qt::WindowFlags wFlags) :
        QChart(QChart::ChartTypeCartesian, parent, wFlags) {
    this->setTitle(config->title);
    // x axis
    this->xAxis.setTickCount(10);
    this->xAxis.setFormat(config->xaxis.type);
    std::string axisName(config->xaxis.name);
    axisName += " ";
    axisName += config->xaxis.unit;
    this->xAxis.setTitleText(axisName.c_str());
    this->xAxisName = config->xaxis.name;
    this->addAxis(&this->xAxis, Qt::AlignBottom);
    this->xmin = config->xaxis.min;
    this->xoriginal = this->xmin;
    this->xmax = config->xaxis.max;
    QDateTime now = QDateTime::fromMSecsSinceEpoch(config->xaxis.min);
    QDateTime max = QDateTime::fromMSecsSinceEpoch(config->xaxis.max);
    this->xAxis.setRange(now, max);

    QPen pen(Chart::getNextColor());
    pen.setWidth(3);
    this->series1.setPen(pen);
    this->series1.setName(config->yaxis1.name);

    //series1.setUseOpenGL(true);
    this->addSeries(&this->series1);
    this->legend()->hide();

    this->yAxis1.setLabelFormat(config->yaxis1.type);
    axisName = config->yaxis1.name;
    axisName += " ";
    axisName += config->yaxis1.unit;
    this->yAxis1.setTitleText(axisName.c_str());
    this->y1AxisName = config->yaxis1.name;
    this->y1min = config->yaxis1.min;
    this->y1max = config->yaxis1.max;
    this->yAxis1.setRange(this->y1min, this->y1max);
    this->addAxis(&this->yAxis1, Qt::AlignLeft);

    this->series1.attachAxis(&this->yAxis1);
    this->series1.attachAxis(&this->xAxis);

    if (config->yaxis2.name != nullptr) {
        this->secondCurveEnabled = true;    
        QPen pen2(Chart::getNextColor());
        pen2.setWidth(3);
        this->series2.setPen(pen2);
        this->series2.setName(config->yaxis2.name);
        // TODO: ver por qué se jode el grafico cuando habilito la renderizacion
        // por openGL
        //series2.setUseOpenGL(true);
        this->addSeries(&this->series2);
        this->legend()->hide();

        this->yAxis2.setLabelFormat(config->yaxis2.type);
        axisName = config->yaxis2.name;
        axisName += " ";
        axisName += config->yaxis2.unit;
        this->yAxis2.setTitleText(axisName.c_str());
        this->y2AxisName = config->yaxis2.name;
        this->yAxis2.setRange(config->yaxis2.min,config->yaxis2.max);

        this->addAxis(&this->yAxis2, Qt::AlignRight);
        this->series2.attachAxis(&this->yAxis2);
        this->series2.attachAxis(&this->xAxis);

        this->y2min = 0;
        this->y2max = 100;
    }

    // Seems that QGraphicsView (QChartView) does not grab gestures.
    // They can only be grabbed here in the QGraphicsWidget (QChart).
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);

}

Chart::~Chart() {
    this->acceptData = false;
}

void Chart::append(double x, double y, unsigned int id) {
    QMutexLocker lock(&this->mutex);
    if (!acceptData) {
        return;
    }

    if ((this->interval_series1.tack() < MIMINUM_INTERVAL_TO_ACCEPT_DATA && id == 1) ||
        (this->interval_series2.tack() < MIMINUM_INTERVAL_TO_ACCEPT_DATA && id == 2)) {
        return;
    }

    if (x > this->xAxis.max().toMSecsSinceEpoch()) {
        this->scroll(x - this->xAxis.max().toMSecsSinceEpoch() + 1000, 0);
    }

    if (id == 1) {
        this->interval_series1.tick();
        this->series1.append(x, y);
        if (y > this->yAxis1.max()) {
            y1min = this->yAxis1.min();
            y1max = y + 50;
            if (this->auto_scroll_enabled)
                this->yAxis1.setRange(y1min, y1max);
        } else if ( y < this->yAxis1.min()) {
            y1min = y - 50;
            y1max = this->yAxis1.max();
            if (this->auto_scroll_enabled)
                this->yAxis1.setRange(y1min, y1max);
        }
    } else {
        this->interval_series2.tick();
        if (this->secondCurveEnabled) {
            this->series2.append(x, y);
            if (y > this->yAxis2.max()) {
                y2min = this->yAxis2.min();
                y2max = y + 50;
                if (this->auto_scroll_enabled)
                    this->yAxis2.setRange(y2min, y2max);
            } else if ( y < this->yAxis2.min()) {
                y2min = y - 50;
                y2max = this->yAxis2.max();
                if (this->auto_scroll_enabled)
                    this->yAxis2.setRange(y2min, y2max);
            }
        }
    }
}

void Chart::init() {
    QMutexLocker lock(&this->mutex);
    this->acceptData = true;
}

void Chart::stop() {
    QMutexLocker lock(&this->mutex);
    this->acceptData = false;
    //TODO: preguntarle al usuario si desea guardar los datos antes de irse
    this->series1.clear();
    this->series2.clear();
}

void Chart::stopFollow() {
    QMutexLocker lock(&this->mutex);
    this->auto_scroll_enabled = false;
}

void Chart::startFollow() {
    QMutexLocker lock(&this->mutex);
    this->auto_scroll_enabled = true;
}

bool Chart::sceneEvent(QEvent *event)
{
    if (event->type() == QEvent::Gesture) {
        return gestureEvent(static_cast<QGestureEvent *>(event));
    }
    return QChart::event(event);
}

bool Chart::gestureEvent(QGestureEvent *event)
{
    if (QGesture *gesture = event->gesture(Qt::PanGesture)) {
        QPanGesture *pan = static_cast<QPanGesture *>(gesture);
        QChart::scroll(-(pan->delta().x()), pan->delta().y());
    }

    if (QGesture *gesture = event->gesture(Qt::PinchGesture)) {
        QPinchGesture *pinch = static_cast<QPinchGesture *>(gesture);
        if (pinch->changeFlags() & QPinchGesture::ScaleFactorChanged)
            QChart::zoom(pinch->scaleFactor());
    }

    return true;
}

void Chart::scroll(qreal dx, qreal dy) {
    std::uint64_t shift = dx;
    this->xmin = this->xAxis.min().toMSecsSinceEpoch() + shift;
    this->xmax = this->xAxis.max().toMSecsSinceEpoch() + shift;
    QDateTime now = QDateTime::fromMSecsSinceEpoch(this->xmin);
    QDateTime max = QDateTime::fromMSecsSinceEpoch(this->xmax);
    if (this->auto_scroll_enabled) {
        this->xAxis.setRange(now, max);
        QChart::scroll(0, dy);
    }
}

void Chart::adjustView() {
    QDateTime now = QDateTime::fromMSecsSinceEpoch(this->xoriginal);
    QDateTime max = QDateTime::fromMSecsSinceEpoch(this->xmax);
    this->xAxis.setRange(now, max);
    this->yAxis1.setRange(this->y1min, this->y1max);
    this->yAxis2.setRange(this->y2min, this->y2max);
}

ChartLimits Chart::getLimits() const {
    QDateTime min = QDateTime::fromMSecsSinceEpoch(this->xmin);
    QDateTime max = QDateTime::fromMSecsSinceEpoch(this->xmax);
    ChartLimits limits(min, max, y1min, y1max, y2min, y2max, 0, 0, 0, 0);
    return std::move(limits);
}

void Chart::setLimits(const ChartLimits &limits) {
    QMutexLocker lock(&this->mutex);
    this->y1min = limits.y1_min;
    this->y1max = limits.y1_max;
    this->y2min = limits.y2_min;
    this->y2max = limits.y2_max;
    this->xmin = limits.time_min.toMSecsSinceEpoch();
    this->xmax = limits.time_max.toMSecsSinceEpoch();
    this->xAxis.setRange(limits.time_min, limits.time_max);
    this->yAxis1.setRange(limits.y1_min, limits.y1_max);
    this->yAxis2.setRange(limits.y2_min, limits.y2_max);
}
