#ifndef EQUIPMENT_STATUS_VIEW_H
#define EQUIPMENT_STATUS_VIEW_H

#include <QWidget>
#include "../connection/serialport.h"

namespace Ui {
class EquipmentStatusView;
}

class EquipmentStatusView : public QWidget
{
    Q_OBJECT

public:
    explicit EquipmentStatusView(QWidget *parent, SerialPort *pPort);
    ~EquipmentStatusView();

public slots:
    void insert(QString, QString);
    void onSerialPortConnected();
    void onSerialPortDisconnected();

private:
    Ui::EquipmentStatusView *ui;
    SerialPort *port;
};

#endif // EQUIPMENT_STATUS_VIEW_H
