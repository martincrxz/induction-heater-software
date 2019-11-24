#ifndef __CONTROL_CONFIGURATION_H__
#define __CONTROL_CONFIGURATION_H__

#include <QWidget>
#include <memory>

#include "../../control/algorithm.h"

#define ERROR   1
#define OK      0

class ControlConfiguration : public QWidget
{
    Q_OBJECT
public:
    explicit ControlConfiguration(QWidget *parent = nullptr);
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
protected:
    std::unique_ptr<Algorithm> controlAlgorithm;

signals:
    void message(const char *str, unsigned char mode);

public slots:
};

#endif // __CONTROL_CONFIGURATION_H__
