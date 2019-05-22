#include "automatic_control_tab_view.h"
#include "ui_automatic_control_tab_view.h"

AutomaticControlTabView::AutomaticControlTabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutomaticControlTabView)
{
    ui->setupUi(this);
}

AutomaticControlTabView::~AutomaticControlTabView()
{
    delete ui;
}
