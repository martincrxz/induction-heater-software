#ifndef __CONTROL_CONFIGURATION_H__
#define __CONTROL_CONFIGURATION_H__

#include <QDoubleValidator>
#include <QString>
#include <QWidget>
#include <memory>

#include "../../control/control_algorithm.h"
#include "../../connection/protocol/temperature_reading.h"

#define FILE_PATH "./classic_control_parameters.txt"
#define ERROR   1
#define OK      0

class ControlConfiguration : public QWidget
{
    Q_OBJECT
public:
    ControlConfiguration(QWidget *parent, SerialPort *sp);
    virtual ~ControlConfiguration();
    /**
     * @brief Valida el input del usuario. Se usa tanto para
     * activar el control, como para guardar los datos en un
     * archivo
     * @return
     */
    virtual bool validateInput() = 0;
    /**
     * @brief Instanciará un objeto que hereda de ALgorithm.
     * Luego se ejecutará a este en un hilo aparte
     * @param targetTemperature
     */
    void start();
    /**
     * @brief Si el hilo existe, detiene su ejecución y libera
     * sus recursos, dejando a nullptr el smart pointer
     */
    void stop();
    /**
     * @brief instancia el tipo de control de forma polimorfica
     */
    virtual void instantiate() = 0;
    /**
     * @brief devuelve el nombre del tipo de control
     * @return
     */
    virtual const char * getName() = 0;
    void dataAvailable(TemperatureReading &temp);
protected:
    SerialPort *sp;
    std::unique_ptr<ControlAlgorithm> controlAlgorithm;

signals:
    void message(const char *str, unsigned char mode);

public slots:
};

#endif // __CONTROL_CONFIGURATION_H__
