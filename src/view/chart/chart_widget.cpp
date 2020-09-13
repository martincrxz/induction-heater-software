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
        "Mediciones de temperatura y potencia");
    
    temp_power_chart = new Chart(&config);
    temp_chart_view = new ChartView(temp_power_chart);

    this->ui->verticalLayout->addWidget(this->temp_chart_view);
    this->temp_chart_view->setRenderHint(QPainter::Antialiasing);

    AxisConfiguration currentAxis("Corriente (A)", "%i", 0, 50);
    AxisConfiguration frequencyAxis("Frecuencia (kHz)", "%i", 0, 50);
    ChartConfiguration current_config(timeAxis, currentAxis, frequencyAxis, 
        "Mediciones de corriente");
    current_chart = new Chart(&current_config);
    current_chart_view = new ChartView(current_chart);

    this->ui->verticalLayout->addWidget(this->current_chart_view);
    this->current_chart_view->setRenderHint(QPainter::Antialiasing);
    
    this->grabGesture(Qt::PanGesture);
    this->grabGesture(Qt::PinchGesture);
}

ChartWidget::~ChartWidget()
{
    delete ui;
    delete this->temp_power_chart;
    delete this->temp_chart_view;
    delete this->current_chart;
    delete this->current_chart_view;
}

void ChartWidget::init() {
    this->temp_power_chart->init();
    this->current_chart->init();
}

void ChartWidget::closeEvent(QCloseEvent *event) {
    this->temp_power_chart->stop();
    this->current_chart->stop();
    QWidget::closeEvent(event);
}


void ChartWidget::dataAvailable(TemperatureReading &temp) {
    this->temp_power_chart->dataAvailable(temp.getData(), 1);
}

void ChartWidget::dataAvailable(PowerSetAcknowledge &power) {
    this->temp_power_chart->dataAvailable(power.getPower(), 2);
}

void ChartWidget::dataAvailable(CurrentFrequencyReading &freq) {
    this->current_chart->dataAvailable(freq.getData(), 2);
}

void ChartWidget::dataAvailable(CurrentRMSReading &current) {
    this->current_chart->dataAvailable(current.getData(), 1);
}

void ChartWidget::on_stopFollowButton_clicked()
{
    this->temp_power_chart->stopFollow();
    this->current_chart->stopFollow();
}

void ChartWidget::on_enableFollowButton_clicked()
{
    this->temp_power_chart->startFollow();
    this->current_chart->startFollow();
}

void ChartWidget::on_fitViewButton_clicked()
{
    this->temp_power_chart->adjustView();
    this->current_chart->adjustView();
}

void ChartWidget::on_saveButton_clicked()
{
    this->temp_power_chart->save();
    this->current_chart->save();
}

void ChartWidget::on_settingsButton_clicked()
{
    QDialog *dialog = new ChartConfigDialog(this->temp_power_chart->getLimits(), this->temp_power_chart);
    dialog->setWindowTitle("Ajuste de gráfico");
    dialog->show();
}
