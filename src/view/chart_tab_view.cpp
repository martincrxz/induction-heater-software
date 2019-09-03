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
        ui(new Ui::ChartTabView),
        chart(new Chart) {
    this->ui->setupUi(this);
    this->ui->chartLayout->addWidget(&this->chartView);
    this->ui->chartLayout->addWidget(&this->initChartButton);
    /**
      * Conecto la señal onClick del botón para que ejecute
      * el método correspondiente
      */
    this->initChartButton.connect(&this->initChartButton, &QPushButton::clicked,
                                  this, &ChartTabView::onInitChartClicked);

    this->chartView.setChart(this->chart);
    this->chartView.setRenderHint(QPainter::Antialiasing);
}

ChartTabView::~ChartTabView() {
    delete this->ui;
    delete this->chart;
}

void ChartTabView::onInitChartClicked() {
    Logger::info("hola");
    this->chart->init();
}
