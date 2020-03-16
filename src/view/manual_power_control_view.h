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
     * @brief Habilita (o no) los botones de la vista. Se usa para evitar
     * envio de mensajes al micro que quieran controlar el horno cuando este
     * se encuentre en modo manual.
     * @param enable
     */
    void enableButtons(bool enable);
    ~ManualPowerControlView();

signals:
    void printMessage(const char *str, unsigned char mode, bool reset);    

private slots:
    /**
     * @brief envía un mensaje al micro para setear la potencia del
     * horno
     */
    void on_setPowerButton_clicked();

private:
    Ui::ManualPowerControlView *ui;
    SerialPort *serialPort;
};

#endif // MANUAL_POWER_CONTROL_VIEW_H
