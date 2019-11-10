#include "classic_control_view.h"
#include "ui_classic_control_view.h"

ClassicControlView::ClassicControlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassicControlView)
{
    ui->setupUi(this);
}

ClassicControlView::~ClassicControlView()
{
    delete ui;
}
