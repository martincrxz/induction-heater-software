#ifndef AUTOMATIC_CONTROL_TAB_VIEW_H
#define AUTOMATIC_CONTROL_TAB_VIEW_H

#include <QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QTimer>
#include <vector>
#include <mutex>

#include "control_configuration/control_configuration.h"
#include "../connection/protocol/temperature_reading.h"
#include "../connection/serialport.h"

namespace Ui {
class AutomaticControlTabView;
}

class AutomaticControlTabView : public QWidget
{
    Q_OBJECT

public:

    explicit AutomaticControlTabView(QWidget *parent, SerialPort *pPort);
    ~AutomaticControlTabView();
    /**
     * @brief postea la temperatura leida para calcular la potencia
     * del potenciometro con el algoritmo de control.
     */
    void dataAvailable(TemperatureReading &temp);
    /**
     * @brief Habilita (o no) los botones de la vista. Se usa para evitar
     * envio de mensajes al micro que quieran controlar el horno cuando este
     * se encuentre en modo manual.
     * @param enable
     */
    void enableButtons(bool enable);
    bool isControlActivated();
    void loadFile(std::string file_path);
    /**
     * @brief Returns current process name, or "-" if none is activated
     * @return
     */
    const char * getProcessName();
    void stop(bool printError);

signals:
    void controlAlgorithmDeactivated();
    void controlAlgorithmActivated();
    void printMessage(const char *str, unsigned char mode, bool reset);    

private slots:
    /**
     * @brief Instancia la vista de paráemtros extras para ser
     * cargados por el usuario cuando seleccione el modo de control.
     *
     * @param index
     */
    void on_controlTypeCombo_currentIndexChanged(int index);
    /**
     * @brief chequea que los parámetros estén bien seteados
     * y lanza el hilo de ejecucion
     */
    void on_activateButton_clicked();

public slots:
    /**
     * @brief Detiene el hilo de ejecución (si lo hay) y libera
     * los recursos.
     */
    void on_deactivateButton_clicked();
private:
    void fillControlConfigViews();

    Ui::AutomaticControlTabView *ui;
    SerialPort *port;
    std::vector<ControlConfiguration *> controlConfigViews;
    unsigned int current{0};
    std::recursive_mutex mutex;
    int activatedControlAlgorithmIndex{-1};
};

#endif // AUTOMATIC_CONTROL_TAB_VIEW_H
