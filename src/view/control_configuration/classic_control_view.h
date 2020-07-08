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
    void loadControlValues(std::string filepath = FILE_PATH) override;
    void updateConfig(const AppConfig &conf) override;

private slots:

    void on_saveButton_clicked();
private:
    /**
     * Un workaround para seguir manteniendo la misma interfaz polimorfica 
     * en la clase padre y tener una especialización que depende de donde se 
     * llame revisa o no la validez de la temperatura (por ejempo, cuando 
     * quiero guardar los parámetros de control en el archivo, no quiero
     * que la función me retorne false por no tener una temperatura 
     * puesta, que no se va a grabar en el archivo)
     * @param  check_temp 
     * @return            
     */
    bool validateInput(bool check_temp);

    Ui::ClassicControlView *ui;
    QDoubleValidator *kValidator;
    QDoubleValidator *tempValidator;
    uint8_t           window_size{1};
};

#endif // CLASSIC_CONTROL_VIEW_H
