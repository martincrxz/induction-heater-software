#include "equipment_status_view.h"
#include "ui_equipment_status_view.h"
typedef enum { ERROR_CODE, TIMESTAMP, INFO} error_table_t;

EquipmentStatusView::EquipmentStatusView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EquipmentStatusView)
{
    ui->setupUi(this);
    // TODO: Borrar esto inmediatamente
    ui->errorLogTable->insertRow(ui->errorLogTable->rowCount());
    int row = ui->errorLogTable->rowCount() - 1;
    ui->errorLogTable->setItem(row, ERROR_CODE, new QTableWidgetItem("01"));
    ui->errorLogTable->setItem(row, TIMESTAMP, new QTableWidgetItem("2019-29-30 10:05:26"));
    ui->errorLogTable->setItem(row, INFO, new QTableWidgetItem("Un error cualquiera"));
}

EquipmentStatusView::~EquipmentStatusView()
{
    delete ui;
}
