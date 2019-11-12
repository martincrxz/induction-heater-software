#ifndef FUZZY_CONTROL_VIEW_H
#define FUZZY_CONTROL_VIEW_H

#include <QWidget>
#include "control_configuration.h"

namespace Ui {
class FuzzyControlView;
}

class FuzzyControlView : public ControlConfiguration
{
    Q_OBJECT

public:
    explicit FuzzyControlView(QWidget *parent = 0);
    ~FuzzyControlView();
    bool validateInput() override;

private:
    Ui::FuzzyControlView *ui;
};

#endif // FUZZY_CONTROL_VIEW_H
