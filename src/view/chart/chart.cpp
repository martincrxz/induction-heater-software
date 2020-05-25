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

#define TIME_REJECT_DATA 100

Chart::Chart(ChartConfiguration *config, QGraphicsItem *parent, 
            Qt::WindowFlags wFlags) :
        QChart(QChart::ChartTypeCartesian, parent, wFlags) {
    this->setTitle(config->title);
    // x axis
    this->xAxis.setTickCount(10);
    this->xAxis.setFormat(config->xaxis.type);
    this->xAxis.setTitleText(config->xaxis.name);
    this->xAxisName = config->xaxis.name;
    this->addAxis(&this->xAxis, Qt::AlignBottom);
    this->xmin = config->xaxis.min;
    this->xoriginal = this->xmin;
    this->xmax = config->xaxis.max;
    QDateTime now = QDateTime::fromMSecsSinceEpoch(config->xaxis.min);
    QDateTime max = QDateTime::fromMSecsSinceEpoch(config->xaxis.max);
    this->xAxis.setRange(now, max);

    QPen pen(Qt::blue);
    pen.setWidth(3);
    this->series1.setPen(pen);

    //series1.setUseOpenGL(true);
    this->addSeries(&this->series1);
    this->legend()->hide();

    this->yAxis1.setLabelFormat(config->yaxis1.type);
    this->yAxis1.setTitleText(config->yaxis1.name);
    this->y1AxisName = config->yaxis1.name;
    this->y1min = config->yaxis1.min;
    this->y1max = config->yaxis1.max;
    this->yAxis1.setRange(this->y1min, this->y1max);
    this->addAxis(&this->yAxis1, Qt::AlignLeft);

    this->series1.attachAxis(&this->yAxis1);
    this->series1.attachAxis(&this->xAxis);

    if (config->yaxis2.name != nullptr) {
        this->secondCurveEnabled = true;    
        QPen pen2(Qt::green);
        pen2.setWidth(3);
        this->series2.setPen(pen2);
        // TODO: ver por qué se jode el grafico cuando habilito la renderizacion
        // por openGL
        //series2.setUseOpenGL(true);
        this->addSeries(&this->series2);
        this->legend()->hide();

        this->yAxis2.setLabelFormat(config->yaxis2.type);
        this->yAxis2.setTitleText(config->yaxis2.name);
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
/**
 *  Considerando que los puntos vienen de dos series distintas, y que
 *  ambas ocurren de manera asincronica, siendo la primer serie la de mayor
 *  predominancia (la mas frecuente), se repetirá el ultimo valor
 *  de  la segunda serie para que ambas series posean el mismo tamaño.
 *  
 *  Para hacer esto, se insertará una repeticion del ultimo valor insertado
 *  en la lista.
 */
void Chart::append(double x, double y, unsigned int id) {
    if (x > this->xAxis.max().toMSecsSinceEpoch()) {
        this->scroll(x - this->xAxis.max().toMSecsSinceEpoch() + 1000, 0);
    }

    if (id == 1) {
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
        // agrego tantos puntos en la serie 2 como hagan falta para igualar
        // los tamaños de la serie
        if (this->secondCurveEnabled) {
            if (this->series2.count() < this->series1.count()) {
                double y2 = 0;
                if (this->series2.count() > 0) {
                   y2 = this->series2.at(this->series2.count() - 1).y();
                }
                append(x, y2, 2);
            }
        }
    } else {
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

void Chart::dataAvailable(double y, unsigned int id) {
    QMutexLocker lock(&this->mutex);
    if (acceptData) {
        this->append(chrono.now(), y, id);
    }
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

void Chart::save()
{
    QMutexLocker lock(&this->mutex);
    std::fstream file("mediciones.csv", std::ios_base::out);
    file << this->xAxisName << "," << this->y1AxisName;
    if (this->secondCurveEnabled)
            file << "," << this->y2AxisName;
    file << std::endl;
    for (int i = 0, j = 0; i < this->series1.count(); ++i) {
        QDateTime x = QDateTime::fromMSecsSinceEpoch(this->series1.at(i).x());
        qreal y1 = this->series1.at(i).y();
        file << x.toString("hh:ss:mm").toStdString() << "," << y1;
        if (this->secondCurveEnabled) {
            if (i < this->series2.count())
                j = i;
            qreal y2 = this->series2.at(j).y();
            file << "," << y2 << std::endl;
        } else {
            file << std::endl;
        }
    }
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
    ChartLimits limits(min, max, y1min, y1max, y2min, y2max);
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