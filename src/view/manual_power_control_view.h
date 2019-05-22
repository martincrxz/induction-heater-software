#ifndef MANUAL_POWER_CONTROL_VIEW_H
#define MANUAL_POWER_CONTROL_VIEW_H

#include <QWidget>

namespace Ui {
class ManualPowerControlView;
}

class ManualPowerControlView : public QWidget
{
    Q_OBJECT

public:
    explicit ManualPowerControlView(QWidget *parent = 0);
    ~ManualPowerControlView();

private:
    Ui::ManualPowerControlView *ui;
};

#endif // MANUAL_POWER_CONTROL_VIEW_H
