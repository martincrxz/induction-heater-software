#include "general_config_dialog.h"
#include "ui_general_config_dialog.h"
#include "../../configuration/app_config.h"

#include <logger/logger.h>

GeneralConfigDialog::GeneralConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneralConfigDialog)
{
    ui->setupUi(this);
    const ApplicationConfig &config = ApplicationConfig::instance();
    this->ui->temp_window_size->setValue(config.getWindowSize());
    uint8_t log_enabled = config.getLogLevel();
    this->ui->critical_check_box->setChecked(log_enabled & CRITICAL);
    this->ui->warning_check_box->setChecked(log_enabled & WARNING);
    this->ui->info_check_box->setChecked(log_enabled & INFO);
    this->ui->debug_check_box->setChecked(log_enabled & DEBUG);
    this->ui->fatal_check_box->setChecked(log_enabled & FATAL);
}

GeneralConfigDialog::~GeneralConfigDialog()
{
    delete ui;
}

void GeneralConfigDialog::on_buttonBox_accepted()
{
    struct GeneralConfig conf;
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
    ApplicationConfig::instance().updateConfig(conf);
}

void GeneralConfigDialog::on_buttonBox_rejected()
{
	const ApplicationConfig &config = ApplicationConfig::instance();
    this->ui->temp_window_size->setValue(config.getWindowSize());
    uint8_t log_enabled = config.getLogLevel();
    this->ui->critical_check_box->setChecked(log_enabled & CRITICAL);
    this->ui->warning_check_box->setChecked(log_enabled & WARNING);
    this->ui->info_check_box->setChecked(log_enabled & INFO);
    this->ui->debug_check_box->setChecked(log_enabled & DEBUG);
    this->ui->fatal_check_box->setChecked(log_enabled & FATAL);
}
