#ifndef CLASSIC_CONTROL_VIEW_H
#define CLASSIC_CONTROL_VIEW_H

#include <QWidget>
#include <QString>
#include "control_configuration.h"

#define FILE_PATH "./classic_control_parameters.txt"

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

signals:
    void message(const char *str, unsigned char mode);

private slots:
    void on_saveButton_clicked();

private:
    void loadControlValues();

    Ui::ClassicControlView *ui;
};

#endif // CLASSIC_CONTROL_VIEW_H