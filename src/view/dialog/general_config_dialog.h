#ifndef GENERAL_CONFIG_DIALOG_H
#define GENERAL_CONFIG_DIALOG_H

#include <QDialog>

#include "config.h"

namespace Ui {
class GeneralConfigDialog;
}

class GeneralConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeneralConfigDialog(QWidget *parent = 0);
    ~GeneralConfigDialog();
    void updateConfig(AppConfig *conf = nullptr);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void config_changed(const AppConfig conf);

private:
    Ui::GeneralConfigDialog *ui;
    uint8_t previous_log_level{INFO | DEBUG | WARNING | CRITICAL | FATAL};
    uint8_t previous_window_size{1};
};

#endif // GENERAL_CONFIG_DIALOG_H
