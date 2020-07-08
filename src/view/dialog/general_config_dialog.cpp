#include "general_config_dialog.h"
#include "ui_general_config_dialog.h"
#include "config.h"

#include <logger/logger.h>

GeneralConfigDialog::GeneralConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneralConfigDialog)
{
    ui->setupUi(this);
    this->ui->temp_window_size->setValue(this->previous_window_size);
    this->ui->critical_check_box->setChecked(this->previous_log_level & CRITICAL);
    this->ui->warning_check_box->setChecked(this->previous_log_level & WARNING);
    this->ui->info_check_box->setChecked(this->previous_log_level & INFO);
    this->ui->debug_check_box->setChecked(this->previous_log_level & DEBUG);
    this->ui->fatal_check_box->setChecked(this->previous_log_level & FATAL);
}

GeneralConfigDialog::~GeneralConfigDialog()
{
    delete ui;
}

void GeneralConfigDialog::on_buttonBox_accepted()
{
    struct AppConfig conf;
    conf.window_size = this->ui->temp_window_size->value();
    if (this->ui->critical_check_box->isChecked())
        conf.log_level_enabled |= CRITICAL;
    if (this->ui->debug_check_box->isChecked())
        conf.log_level_enabled |= DEBUG;
    if (this->ui->fatal_check_box->isChecked())
        conf.log_level_enabled |= FATAL;
    if (this->ui->info_check_box->isChecked())
        conf.log_level_enabled |= INFO;
    if (this->ui->warning_check_box->isChecked())
        conf.log_level_enabled |= WARNING;
    this->updateConfig(&conf);
}

void GeneralConfigDialog::updateConfig(AppConfig *conf) {
    if (conf) {
        this->previous_log_level = conf->log_level_enabled;
        this->previous_window_size = conf->window_size;
        emit config_changed(*conf);
    } else {
        AppConfig conf;
        conf.log_level_enabled = this->previous_log_level;
        conf.window_size       = this->previous_window_size;
        emit config_changed(conf);
    }
}

void GeneralConfigDialog::on_buttonBox_rejected()
{
    this->ui->temp_window_size->setValue(this->previous_window_size);
    this->ui->critical_check_box->setChecked(this->previous_log_level & CRITICAL);
    this->ui->warning_check_box->setChecked(this->previous_log_level & WARNING);
    this->ui->info_check_box->setChecked(this->previous_log_level & INFO);
    this->ui->debug_check_box->setChecked(this->previous_log_level & DEBUG);
    this->ui->fatal_check_box->setChecked(this->previous_log_level & FATAL);
}
