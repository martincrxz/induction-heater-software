#ifndef CLASSIC_CONTROL_VIEW_H
#define CLASSIC_CONTROL_VIEW_H

#include <QWidget>
#include <QString>
#include <QDoubleValidator>

#include "control_configuration.h"
#include "../../connection/protocol/temperature_reading.h"

namespace Ui {
class ClassicControlView;
}

class ClassicControlView : public ControlConfiguration
{
    Q_OBJECT

public:
    ClassicControlView(QWidget *parent, SerialPort *sp);
    ~ClassicControlView();
    bool validateInput() override;
    /**
     * @brief instancia el algoritmo de control
     * @param objective temperature
     */
    void instantiate() override;
    const char * getName() override;

private slots:
    void on_saveButton_clicked();

private:
    void loadControlValues();
    Ui::ClassicControlView *ui;
    QDoubleValidator *kValidator;
    QDoubleValidator *tempValidator;
};

#endif // CLASSIC_CONTROL_VIEW_H
