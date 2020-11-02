#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <logger/logger.h>
#include <QtGui/QBitmap>
#include <memory>

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
    QPixmap pixmap(":/record.png");
    QBitmap mask = pixmap.createMaskFromColor(Qt::white, Qt::MaskOutColor);
    pixmap.fill((Qt::red));
    pixmap.setMask(mask);
    this->save_button_icon.addPixmap(pixmap, QIcon::Normal,QIcon::Off);
    this->save_button_icon.addPixmap(QPixmap(":/stop.png"), QIcon::Normal,QIcon::On);
    this->ui->saveButton->setIcon(this->save_button_icon);
    this->ui->saveButton->setCheckable(true);
    std::uint64_t now = QDateTime::currentDateTime().toMSecsSinceEpoch();
    AxisConfiguration tempAxis("Temperatura", "(°C)", "%i", 0, 5);
    AxisConfiguration powerAxis("Potencia", "(W)", "%i", 0, 100);
    AxisConfiguration timeAxis("Tiempo", "(HH:mm:ss)", "HH:mm:ss", now, 
        now + TIME_CHART_MAX_RANGE);
    ChartConfiguration config(timeAxis, tempAxis, powerAxis, 
        "Mediciones de temperatura y potencia");
    
    temp_power_chart = new Chart(&config);
    temp_chart_view = new ChartView(temp_power_chart);

    this->ui->verticalLayout->addWidget(this->temp_chart_view);
    this->temp_chart_view->setRenderHint(QPainter::Antialiasing);

    AxisConfiguration currentAxis("Corriente", "(A)", "%i", 0, 50);
    AxisConfiguration frequencyAxis("Frecuencia", "(kHz)", "%i", 0, 50);
    ChartConfiguration current_config(timeAxis, currentAxis, frequencyAxis, 
        "Mediciones de corriente");
    current_chart = new Chart(&current_config);
    current_chart_view = new ChartView(current_chart);

    this->ui->verticalLayout->addWidget(this->current_chart_view);

    //Activo las leyendas
    current_chart->legend()->setVisible(true);
    current_chart->legend()->setAlignment(Qt::AlignBottom);
    temp_power_chart->legend()->setVisible(true);
    temp_power_chart->legend()->setAlignment(Qt::AlignBottom);

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
    if (this->ui->saveButton->isChecked())
        this->ui->saveButton->click();
    this->temp_power_chart->stop();
    this->current_chart->stop();
    QWidget::closeEvent(event);
}

void ChartWidget::appendData(Chart *chart, double now, double data, PointType type) {
    chart->append(now, data,  type == PointType::TEMPERATURE || type == PointType::CURRENT ? 1 : 2);
    if (writer != nullptr)
        this->writer->pushPoint(ChartPoint(now, data, type));
}

void ChartWidget::dataAvailable(TemperatureReading &temp) {
    appendData(this->temp_power_chart, chrono.now(), temp.getData(), PointType::TEMPERATURE);
}

void ChartWidget::dataAvailable(PowerSetAcknowledge &power) {
    appendData(this->temp_power_chart, chrono.now(), power.getPower(), PointType::POWER);
}

void ChartWidget::dataAvailable(CurrentFrequencyReading &freq) {
    appendData(this->current_chart, chrono.now(), freq.getData(), PointType::FRECUENCY);
}

void ChartWidget::dataAvailable(CurrentRMSReading &current) {
    appendData(this->current_chart, chrono.now(), current.getData(), PointType::CURRENT);
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
    if (this->ui->saveButton->isChecked()) {
        QString dir = QFileDialog::getExistingDirectory(this, tr("Seleccione carpeta donde guardar los archivos"),
                                                        ".",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
        Logger::critical("Arrancando el escritor de gráficos.");
        this->writer = std::make_unique<ChartFileWriter>(dir.toStdString());
    } else {
        Logger::critical("Parando el escritor de los gráficos.");
        this->writer->stop();

    }
}

void ChartWidget::on_settingsButton_clicked()
{
    ChartLimits limits = this->temp_power_chart->getLimits();
    ChartLimits current_limits = this->current_chart->getLimits();
    limits.y3_min = current_limits.y1_min;
    limits.y3_max = current_limits.y1_max;
    limits.y4_min = current_limits.y2_min;
    limits.y4_max = current_limits.y2_max;
    QDialog *dialog = new ChartConfigDialog(limits, this->temp_power_chart, this->current_chart);
    dialog->setWindowTitle("Ajuste de gráfico");
    dialog->show();
}
