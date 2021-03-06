/*
 * Created by Federico Manuel Gomez Peter
 * on 20/8/19.
 */

#ifndef __CHART_H__
#define __CHART_H__

#include <chrono.h>
#include <QString>
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
//#include <QtCharts/QSplineSeries>
#include <QtCore/QDateTime>
#include <QtCore/QMutex>
#include <QColor>
#include <cstdint>

#include "../../connection/protocol/temperature_reading.h"
#include "chart_conf.h"
#include "chart_limits.h"
/**
 * Intervalo en milisegundos que debe transcurrir para acetar un punto del gráfico.
 */
#define MIMINUM_INTERVAL_TO_ACCEPT_DATA 10

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
    void stopFollow();
    void startFollow();
    /**
     * @brief       Debido a que en el eje X (eje temporal) no está bien
     *              definido en QT la magnitud en la que se desplaza (no te
     *              desplzás en micro segundos, un scroll(100, 0)
     *              aproximadamente es de 1 segundo) sobreescribo el metodo
     *              para hacer un desplazamiento mas especifico (aunque
     *              pagando en copias de variables)
     *              
     * @param dx    Desplazamiento del tiempo (en milisegundos)
     * @param dy    Desplazamiento absoluto en y
     */
    void scroll(qreal dx, qreal dy);
    void append(double x, double y, unsigned int id = 1);
    void adjustView();
    ChartLimits getLimits() const;
    void setLimits(const ChartLimits &limits);


protected:
    bool sceneEvent(QEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);
    static QColor getNextColor();
    bool secondCurveEnabled{false};
    double y1min{0};
    double y1max{0};
    double y2min{0};
    double y2max{0};
    std::uint64_t xoriginal{0};
    std::uint64_t xmin{0};
    std::uint64_t xmax{0};
    QLineSeries series1;
    QLineSeries series2;
    QDateTimeAxis xAxis;
    QValueAxis yAxis1;
    QValueAxis yAxis2;
    const char * xAxisName;
    const char * y1AxisName;
    const char * y2AxisName;
    QMutex mutex;
    bool acceptData;
    Chrono interval_series1;
    Chrono interval_series2;
    bool auto_scroll_enabled{true};
};


#endif // __CHART_H__
