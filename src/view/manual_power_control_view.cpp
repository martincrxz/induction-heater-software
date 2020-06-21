#include <QString>
#include <logger/logger.h>

#include "../connection/protocol/micro_message.h"
#include "../connection/protocol/set_power.h"
#include "../control/control_algorithm.h"
#include "manual_power_control_view.h"
#include "ui_manual_power_control_view.h"
#include "message_modes.h"

#include <iostream>

ManualPowerControlView::ManualPowerControlView(QWidget *parent, SerialPort *pPort):
    QWidget(parent),
    ui(new Ui::ManualPowerControlView),
    serialPort(pPort)
{
    ui->setupUi(this);
 }

ManualPowerControlView::~ManualPowerControlView()
{
    delete ui;
}

void ManualPowerControlView::on_setPowerButton_clicked()
{
    float powerValue = this->ui->powerValue->text().toFloat();
    if (powerValue < 0 || powerValue > 100) {
        emit printMessage("Potencia inválida", ERROR, true);
        return;
    }
    /*
     *  Si la potencia a setearle al horno es menor a 10, el horno se apaga por
     *  una protección contra cortocircuito.
     */

    /*
    //TODO: refactor this, cambiar el valor en función de lo que recibe de powerTOTaps
    if (powerValue < 10) {
        this->ui->powerValue->setValue(10);
    }

    if (powerValue > 100) {
        this->ui->powerValue->setValue(100);   
    }
    */
    unsigned char taps = ControlAlgorithm::powerToTaps(powerValue);
    std::shared_ptr<OutgoingMessage> toSend(new SetPower(taps));
    this->serialPort->send(toSend);
    emit printMessage("Mensaje enviado", OK, true);
}

void ManualPowerControlView::enableButtons(bool enable) {
    this->ui->setPowerButton->setEnabled(enable);
}
