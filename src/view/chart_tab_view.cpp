#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

#include "chart_tab_view.h"
#include "ui_chart_tab_view.h"
#include "exception.h"

ChartTabView::ChartTabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartTabView)
{
    ui->setupUi(this);
    ui->chartLayout->addWidget(&this->chartView);
    ui->chartLayout->addWidget(&this->initChartButton);
    /**
      * Conecto la señal onClick del botón para que ejecute
      * el método correspondiente
      */
    this->initChartButton.connect(&this->initChartButton, &QPushButton::clicked,
                                  this, &ChartTabView::onInitChartClicked);

    // inicializo el gráfico
    this->chart.addSeries(&this->series);
    this->chart.legend()->hide();
    this->chart.setTitle("Mediciones del temperatura");

    this->xAxis.setTickCount(10);
    this->xAxis.setFormat("HH mm ss");
    this->xAxis.setTitleText("Tiempo");

    this->yAxis.setLabelFormat("%i");
    this->yAxis.setTitleText("Temperatura (°C)");

    this->chart.addAxis(&this->xAxis, Qt::AlignBottom);
    this->series.attachAxis(&this->xAxis);
    this->chart.addAxis(&this->yAxis, Qt::AlignLeft);
    this->series.attachAxis(&this->yAxis);

    this->chartView.setChart(&this->chart);
    this->chartView.setRenderHint(QPainter::Antialiasing);

}

ChartTabView::~ChartTabView()
{
    delete ui;
}

void ChartTabView::onInitChartClicked()
{

}

