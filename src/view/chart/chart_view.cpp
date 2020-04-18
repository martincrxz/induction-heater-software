#include "chart_view.h"

#include <logger/logger.h>
#include <QtGui/QMouseEvent>

ChartView::ChartView(Chart *chart, QWidget *parent) :
    QChartView(chart, parent),
    m_isTouching(false),
    chart(chart)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

bool ChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;
    }
    return QChartView::viewportEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching)
        m_isTouching = false;

    QChartView::mouseReleaseEvent(event);
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    this->chart->stopFollow();
    switch (event->key()) {
    case Qt::Key_Plus:
        chart->zoomIn();
        break;
    case Qt::Key_Minus:
        chart->zoomOut();
        break;
    case Qt::Key_Left:
        chart->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
