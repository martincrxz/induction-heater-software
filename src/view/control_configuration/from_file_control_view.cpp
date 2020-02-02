#include "from_file_control_view.h"
#include "ui_from_file_control_view.h"

FromFileControlView::FromFileControlView(QWidget *parent, SerialPort *s) :
    ControlConfiguration(parent, s),
    ui(new Ui::FromFileControlView)
{
    ui->setupUi(this);
}

FromFileControlView::~FromFileControlView()
{
    delete ui;
}

bool FromFileControlView::validateInput()
{
    return true;
}

void FromFileControlView::instantiate() {
    this->controlAlgorithm.reset(nullptr);
}

const char *FromFileControlView::getName()
{
    return "Desde archivo";
}
