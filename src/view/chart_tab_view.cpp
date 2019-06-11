#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

#include "chart_tab_view.h"
#include "ui_chart_tab_view.h"

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
}

ChartTabView::~ChartTabView()
{
    delete ui;
}

void ChartTabView::onInitChartClicked()
{
    // TODO refactor this
    //![1]
    QLineSeries *series = new QLineSeries();
    //![1]

    //![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Sunspots count (by Space Weather Prediction Center)");
    //![3]

    //![4]
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Sunspots count");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    this->chartView.setChart(chart);
//    QChartView *chartView = new QChartView(chart);
    chartView.setRenderHint(QPainter::Antialiasing);
    //![5]

}
