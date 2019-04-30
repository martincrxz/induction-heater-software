#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../model/errorTableColums.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // TODO: Borrar esto inmediatamente
    ui->errorLogTable->insertRow(ui->errorLogTable->rowCount());
    int row = ui->errorLogTable->rowCount() - 1;
    ui->errorLogTable->setItem(row, ERROR_CODE, new QTableWidgetItem("01"));
    ui->errorLogTable->setItem(row, TIMESTAMP, new QTableWidgetItem("2019-29-30 10:05:26"));
    ui->errorLogTable->setItem(row, INFO, new QTableWidgetItem("Un error cualquiera"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

