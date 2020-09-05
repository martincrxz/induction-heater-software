#include <QDialog>
#include <logger/logger.h>

#include "chart_conf.h"
#include "chart_config_dialog.h"
#include "chart_widget.h"
#include "ui_chart_widget.h"

#define TIME_CHART_MAX_RANGE 10000

ChartWidget::ChartWidget(QWidget *parent) :
QWidget(parent),
ui(new Ui::ChartWidget)
{
    ui->setupUi(this);
    std::uint64_t now = QDateTime::currentDateTime().toMSecsSinceEpoch();
    AxisConfiguration tempAxis("Temperatura (°C)", "%i", 0, 5);
    AxisConfiguration powerAxis("Potencia (W)", "%i", 0, 100);
    AxisConfiguration timeAxis("Tiempo (HH:mm:ss)", "HH:mm:ss", now, 
        now + TIME_CHART_MAX_RANGE);
    ChartConfiguration config(timeAxis, tempAxis, powerAxis, 
        "Mediciones del horno");
    
    temp_power_chart = new Chart(&config);
    chartView = new ChartView(temp_power_chart);

    this->ui->verticalLayout->addWidget(this->chartView);
    this->chartView->setRenderHint(QPainter::Antialiasing);

    this->grabGesture(Qt::PanGesture);
    this->grabGesture(Qt::PinchGesture);
}

ChartWidget::~ChartWidget()
{
    delete ui;
    delete this->temp_power_chart;
    delete this->chartView;
}

void ChartWidget::init() {
    this->temp_power_chart->init();
}

void ChartWidget::closeEvent(QCloseEvent *event) {
    this->temp_power_chart->stop();
    QWidget::closeEvent(event);
}


void ChartWidget::dataAvailable(TemperatureReading &temp) {
    this->temp_power_chart->dataAvailable(temp.getData(), 1);
}

void ChartWidget::dataAvailable(PowerSetAcknowledge &power) {
    this->temp_power_chart->dataAvailable(power.getPower(), 2);
}

void ChartWidget::on_stopFollowButton_clicked()
{
    this->temp_power_chart->stopFollow();
}

void ChartWidget::on_enableFollowButton_clicked()
{
    this->temp_power_chart->startFollow();
}

void ChartWidget::on_fitViewButton_clicked()
{
    this->temp_power_chart->adjustView();
}

void ChartWidget::on_saveButton_clicked()
{
    this->temp_power_chart->save();
}

void ChartWidget::on_settingsButton_clicked()
{
    QDialog *dialog = new ChartConfigDialog(this->temp_power_chart->getLimits(), this->temp_power_chart);
    dialog->setWindowTitle("Ajuste de gráfico");
    dialog->show();
}
