#include <logger/logger.h>

#include "chart_widget.h"
#include "ui_chart_widget.h"

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWidget)
{
    ui->setupUi(this);
    ChartConfiguration config {
      "Temperatura (°C)",
      "%i",
      "Potencia (W)",
      "%i",
      "Tiempo",
      "HH:mm:ss",
      "Mediciones del horno"
    };
    chart = new Chart(&config);
	this->ui->verticalLayout->addWidget(&this->chartView);
    this->chartView.setChart(this->chart);
    this->chartView.setRenderHint(QPainter::Antialiasing);
}

ChartWidget::~ChartWidget()
{
    delete ui;
    delete this->chart;
}

void ChartWidget::init() {
	this->chart->init();
}

void ChartWidget::closeEvent(QCloseEvent *event) {
	Logger::info("cerrando");
	this->chart->stop();
	QWidget::closeEvent(event);
}


void ChartWidget::dataAvailable(TemperatureReading &temp) {
	this->chart->dataAvailable(temp.getData(), 1);
}

void ChartWidget::dataAvailable(PowerSetAcknowledge &power) {
    this->chart->dataAvailable(power.getPower(), 2);
}
