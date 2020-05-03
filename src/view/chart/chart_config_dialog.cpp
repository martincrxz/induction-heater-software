#include "chart.h"
#include "chart_config_dialog.h"
#include "ui_chart_config_dialog.h"
#include "logger/logger.h"
#include <iostream>
ChartConfigDialog::ChartConfigDialog(ChartLimits l, Chart *c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartConfigDialog),
    chart(c) {
    ui->setupUi(this);
    this->ui->time_max_edit->setDisplayFormat("dd/MM/yyyy hh:mm:ss");
    this->ui->time_min_edit->setDisplayFormat("dd/MM/yyyy hh:mm:ss");
    this->ui->time_max_edit->setDateTime(l.time_max);
    this->ui->time_min_edit->setDateTime(l.time_min);
    this->ui->temp_max_edit->setText(QString::number(l.y1_max));
    this->ui->temp_min_edit->setText(QString::number(l.y1_min));
    this->ui->power_max_edit->setText(QString::number(l.y2_max));
    this->ui->power_min_edit->setText(QString::number(l.y2_min));
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
        this->ui->power_max_edit->text().toDouble());
    chart->setLimits(limits);
}
