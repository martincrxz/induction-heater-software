#include <QtCore/QDateTime>

#include "equipment_status_view.h"
#include "ui_equipment_status_view.h"
typedef enum { ERROR_CODE, TIMESTAMP, INFO} error_table_t;

EquipmentStatusView::EquipmentStatusView(QWidget *parent, SerialPort *pPort) :
    QWidget(parent),
    ui(new Ui::EquipmentStatusView),
    port(pPort)
{
    ui->setupUi(this);

    connect(port, &SerialPort::serialPortConnected, this, &EquipmentStatusView::onSerialPortConnected);
    connect(port, &SerialPort::serialPortDisconnected, this, &EquipmentStatusView::onSerialPortDisconnected);
}

EquipmentStatusView::~EquipmentStatusView()
{
    delete ui;
}

void EquipmentStatusView::insert(QString code, QString desc){
    std::string currentDatetime = QDateTime::currentDateTime().
            toString("dd/MM/yyyy HH:mm:ss").toStdString();
    ui->errorLogTable->insertRow(ui->errorLogTable->rowCount());
    int row = ui->errorLogTable->rowCount() - 1;
    ui->errorLogTable->setItem(row, ERROR_CODE, new QTableWidgetItem(code));
    ui->errorLogTable->setItem(row, TIMESTAMP, new QTableWidgetItem(currentDatetime.data()));
    ui->errorLogTable->setItem(row, INFO, new QTableWidgetItem(desc));
}

void EquipmentStatusView::onSerialPortConnected() {
    ui->usbPortValue->setText(port->portName());
}

void EquipmentStatusView::onSerialPortDisconnected() {
    ui->usbPortValue->setText("-");
}
