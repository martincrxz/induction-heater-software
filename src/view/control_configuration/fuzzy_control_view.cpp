#include "fuzzy_control_view.h"
#include "ui_fuzzy_control_view.h"

FuzzyControlView::FuzzyControlView(QWidget *parent) :
    ControlConfiguration(parent),
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

void FuzzyControlView::instantiate(float targetTemp) {
    this->controlAlgorithm.reset(nullptr);
}