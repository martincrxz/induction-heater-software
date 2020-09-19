#include "chart.h"
#include "chart_config_dialog.h"
#include "ui_chart_config_dialog.h"
#include "logger/logger.h"
#include <iostream>
ChartConfigDialog::ChartConfigDialog(ChartLimits &l, Chart *c1, Chart *c2, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ChartConfigDialog),
        temp_chart(c1),
        current_chart(c2) {
    ui->setupUi(this);
    this->ui->time_max_edit->setDisplayFormat("dd/MM/yyyy hh:mm:ss");
    this->ui->time_min_edit->setDisplayFormat("dd/MM/yyyy hh:mm:ss");
    this->ui->time_max_edit->setDateTime(l.time_max);
    this->ui->time_min_edit->setDateTime(l.time_min);
    this->ui->temp_max_edit->setText(QString::number(l.y1_max));
    this->ui->temp_min_edit->setText(QString::number(l.y1_min));
    this->ui->power_max_edit->setText(QString::number(l.y2_max));
    this->ui->power_min_edit->setText(QString::number(l.y2_min));
    this->ui->current_max_edit->setText(QString::number(l.y3_max));
    this->ui->current_min_edit->setText(QString::number(l.y3_min));
    this->ui->freq_max_edit->setText(QString::number(l.y4_max));
    this->ui->freq_min_edit->setText(QString::number(l.y4_min));
}

ChartConfigDialog::~ChartConfigDialog() {
    delete ui;
}

void ChartConfigDialog::on_buttonBox_accepted() {
    QDateTime time_max = this->ui->time_max_edit->dateTime();
    QDateTime time_min = this->ui->time_min_edit->dateTime();
    ChartLimits limits(time_min, time_max,
        this->ui->temp_min_edit->text().toDouble(),
        this->ui->temp_max_edit->text().toDouble(),
        this->ui->power_min_edit->text().toDouble(),
        this->ui->power_max_edit->text().toDouble(),
        this->ui->current_min_edit->text().toDouble(),
        this->ui->current_max_edit->text().toDouble(),
        this->ui->freq_min_edit->text().toDouble(),
        this->ui->freq_max_edit->text().toDouble());
    temp_chart->setLimits(limits);
    limits.y1_min = limits.y3_min;
    limits.y1_max = limits.y3_max;
    limits.y2_min = limits.y4_min;
    limits.y2_max = limits.y4_max;
    current_chart->setLimits(limits);
}
