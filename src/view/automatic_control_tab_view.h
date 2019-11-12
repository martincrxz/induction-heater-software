#ifndef AUTOMATIC_CONTROL_TAB_VIEW_H
#define AUTOMATIC_CONTROL_TAB_VIEW_H

#include <QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QTimer>
#include <vector>

#include "control_configuration/control_configuration.h"

namespace Ui {
class AutomaticControlTabView;
}

class AutomaticControlTabView : public QWidget
{
    Q_OBJECT

public:
    explicit AutomaticControlTabView(QWidget *parent = 0);
    ~AutomaticControlTabView();

private slots:
    /**
     * @brief Instancia la vista de paráemtros extras para ser
     * cargados por el usuario cuando seleccione el modo de control.
     *
     * @param index
     */
    void on_controlTypeCombo_currentIndexChanged(int index);
    void on_activateButton_clicked();

private:
    void resetLabel();

    Ui::AutomaticControlTabView *ui;
    QTimer *resetLabelTimer;
    std::vector<ControlConfiguration *> controlConfigViews;
    unsigned int current{0};
};

#endif // AUTOMATIC_CONTROL_TAB_VIEW_H
