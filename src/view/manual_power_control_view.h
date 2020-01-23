#ifndef MANUAL_POWER_CONTROL_VIEW_H
#define MANUAL_POWER_CONTROL_VIEW_H

#include <QWidget>
#include <QIntValidator>

#include "../connection/serialport.h"
namespace Ui {
class ManualPowerControlView;
}

class ManualPowerControlView : public QWidget
{
    Q_OBJECT

public:
    explicit ManualPowerControlView(QWidget *parent, SerialPort *pPort);
    /**
     * @brief Imprime un mensaje de error o de exito al querer enviar
     * un mensaje de seteo de conrol manual
     * @param str
     * @param mode
     */
    void printMessage(const char *str, unsigned char mode = 0);
    /**
     * @brief deja el mensaje de warning con texto vacio
     */
    void resetLabel();
    ~ManualPowerControlView();

private slots:
    /**
     * @brief envía un mensaje al micro para setear la potencia del
     * horno
     */
    void on_setPowerButton_clicked();

private:
    Ui::ManualPowerControlView *ui;
    SerialPort *serialPort;
    QTimer *resetLabelTimer;
};

#endif // MANUAL_POWER_CONTROL_VIEW_H
