#ifndef CLASSIC_CONTROL_VIEW_H
#define CLASSIC_CONTROL_VIEW_H

#include <QWidget>
#include "control_configuration.h"

namespace Ui {
class ClassicControlView;
}

class ClassicControlView : public ControlConfiguration
{
    Q_OBJECT

public:
    explicit ClassicControlView(QWidget *parent = 0);
    ~ClassicControlView();
    bool validateInput() override;

private:
    Ui::ClassicControlView *ui;
};

#endif // CLASSIC_CONTROL_VIEW_H
