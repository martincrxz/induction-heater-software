#include "fuzzy_control_view.h"
#include "ui_fuzzy_control_view.h"

FuzzyControlView::FuzzyControlView(QWidget *parent, SerialPort *s) :
    ControlConfiguration(parent, s),
    ui(new Ui::FuzzyControlView)
{
    ui->setupUi(this);
}

FuzzyControlView::~FuzzyControlView()
{
    delete ui;
}

bool FuzzyControlView::validateInput()
{
    return true;
}

void FuzzyControlView::instantiate() {
    this->controlAlgorithm.reset(nullptr);
}

const char *FuzzyControlView::getName()
{
    return "Fuzzy logic";
}
