#ifndef CHART_CONFIG_DIALOG_H
#define CHART_CONFIG_DIALOG_H

#include <QDialog>
#include "chart_limits.h"

namespace Ui {
class ChartConfigDialog;
}
// Forward declaration para evitar referencia circular
class Chart;

class ChartConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ChartConfigDialog(ChartLimits l, Chart *chart, QWidget *parent = 0);
    ~ChartConfigDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ChartConfigDialog *ui;
    Chart *chart;
};

#endif // CHART_CONFIG_DIALOG_H
