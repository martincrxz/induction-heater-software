#ifndef GENERAL_CONFIG_DIALOG_H
#define GENERAL_CONFIG_DIALOG_H

#include <QDialog>

#include "../../configuration/general_config.h"

namespace Ui {
class GeneralConfigDialog;
}

class GeneralConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeneralConfigDialog(QWidget *parent = 0);
    ~GeneralConfigDialog();
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::GeneralConfigDialog *ui;
};

#endif // GENERAL_CONFIG_DIALOG_H
