#include "chart_tab_view.h"
#include "ui_chart_tab_view.h"

ChartTabView::ChartTabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartTabView)
{
    ui->setupUi(this);
}

ChartTabView::~ChartTabView()
{
    delete ui;
}
