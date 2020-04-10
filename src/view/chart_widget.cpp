#include <logger/logger.h>

#include "chart_configuration/chart_conf.h"
#include "chart_widget.h"
#include "ui_chart_widget.h"

#define TIME_CHART_MAX_RANGE 30000

ChartWidget::ChartWidget(QWidget *parent) :
QWidget(parent),
ui(new Ui::ChartWidget)
{
    ui->setupUi(this);
    std::uint64_t now = QDateTime::currentDateTime().toMSecsSinceEpoch();
    AxisConfiguration tempAxis("Temperatura (°C)", "%i", 0, 5);
    AxisConfiguration powerAxis("Potencia (W)", "%i", 0, 100);
    AxisConfiguration timeAxis("Tiempo", "HH:mm:ss", now, 
        now + TIME_CHART_MAX_RANGE);
    ChartConfiguration config(timeAxis, tempAxis, powerAxis, 
        "Mediciones del horno");
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
