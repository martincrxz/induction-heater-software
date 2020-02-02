#ifndef FROM_FILE_CONTROL_VIEW_H
#define FROM_FILE_CONTROL_VIEW_H

#include <QWidget>
#include "control_configuration.h"

namespace Ui {
class FromFileControlView;
}

class FromFileControlView: public ControlConfiguration
{
    Q_OBJECT

public:
    explicit FromFileControlView(QWidget *parent, SerialPort *sp);
    ~FromFileControlView();
    bool validateInput() override;
    void instantiate() override;
    const char * getName() override;

private:
    Ui::FromFileControlView *ui;
};

#endif // FROM_FILE_CONTROL_VIEW_H
