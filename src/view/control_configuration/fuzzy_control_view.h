#ifndef FUZZY_CONTROL_VIEW_H
#define FUZZY_CONTROL_VIEW_H

#include <QString>
#include <QWidget>
#include "control_configuration.h"

namespace Ui {
class FuzzyControlView;
}

class FuzzyControlView : public ControlConfiguration
{
    Q_OBJECT

public:
    FuzzyControlView(QWidget *parent, SerialPort *sp);
    ~FuzzyControlView();
    bool validateInput() override;
    void instantiate() override;
    const char * getName() override;
    void loadControlValues(std::string filepath = FILE_PATH) override;
    
private slots:
    void on_operationModeCombo_currentIndexChanged(int index);

private:
    Ui::FuzzyControlView *ui;
};

#endif // FUZZY_CONTROL_VIEW_H
