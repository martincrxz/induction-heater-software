#include "equipment_status_view.h"
#include "ui_equipment_status_view.h"
typedef enum { ERROR_CODE, TIMESTAMP, INFO} error_table_t;

EquipmentStatusView::EquipmentStatusView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EquipmentStatusView)
{
    ui->setupUi(this);
}

EquipmentStatusView::~EquipmentStatusView()
{
    delete ui;
}

void EquipmentStatusView::insert(QString code, QString ts, QString desc){
    ui->errorLogTable->insertRow(ui->errorLogTable->rowCount());
    int row = ui->errorLogTable->rowCount() - 1;
    ui->errorLogTable->setItem(row, ERROR_CODE, new QTableWidgetItem(code));
    ui->errorLogTable->setItem(row, TIMESTAMP, new QTableWidgetItem(ts));
    ui->errorLogTable->setItem(row, INFO, new QTableWidgetItem(desc));
}