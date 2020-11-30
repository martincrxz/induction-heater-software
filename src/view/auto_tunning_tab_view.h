#ifndef AUTO_TUNNING_TAB_VIEW_H
#define AUTO_TUNNING_TAB_VIEW_H

#include <QWidget>
#include <QIntValidator>
#include <QDoubleValidator>

#include "../connection/serialport.h"
#include "../control/zieglers_nichols.h"

namespace Ui {
class AutoTunningTabView;
}

class MainWindow;

class AutoTunningTabView : public QWidget
{
    Q_OBJECT

public:
    explicit AutoTunningTabView(QWidget *parent, SerialPort *port);
    ~AutoTunningTabView();
    /**
     * @brief Habilita (o no) los botones de la vista. Se usa para evitar
     * envio de mensajes al micro que quieran controlar el horno cuando este
     * se encuentre en modo manual.
     * @param enable
     */
    void enableButtons(bool enable);
    void znCalculated(float &kp, float &kd, float &ki);
    void stop(bool finished, bool printError);
    void autotunningFailed(const char *reason);
    void dataAvailable(TemperatureReading &temp);

signals:
    void ZNCalculated(float kp, float ki, float kd);
    void printMessage(const char *str, unsigned char mode, bool reset);

public slots:
    void activate();
    void deactivate(bool finished = false);

private:
    bool validateInput();
    Ui::AutoTunningTabView *ui;
    MainWindow* mainWindow;
    SerialPort *port;
    std::unique_ptr<ZieglerNichols> zn;
    QIntValidator *powerValidator;
    QDoubleValidator *tempValidator;
};

#endif // AUTO_TUNNING_TAB_VIEW_H
