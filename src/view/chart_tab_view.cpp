#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QDebug>
#include <logger/logger.h>

#include "chart_tab_view.h"
#include "ui_chart_tab_view.h"
#include "exception.h"

ChartTabView::ChartTabView(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ChartTabView) {
    this->ui->setupUi(this);
    this->widget = new ChartWidget();
}

ChartTabView::~ChartTabView() {
    delete this->ui;
}

void ChartTabView::dataAvailable(TemperatureReading &temp) {
    this->widget->dataAvailable(temp);
}

void ChartTabView::dataAvailable(PowerSetAcknowledge &power) {
    this->widget->dataAvailable(power);
}

void ChartTabView::dataAvailable(CurrentFrequencyReading &freq) {
    this->widget->dataAvailable(freq);
}

void ChartTabView::dataAvailable(CurrentRMSReading &current) {
    this->widget->dataAvailable(current);
}

void ChartTabView::on_initChartButton_clicked() {
    this->widget->show();
    this->widget->init();
}
