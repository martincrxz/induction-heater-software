#include "fuzzy_control_view.h"
#include "ui_fuzzy_control_view.h"

#include "../../control/fuzzy_logic.h"

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
    float targetTemp = this->ui->targetTempLineEdit->text().toFloat();
    this->controlAlgorithm.reset(new FuzzyLogic(targetTemp, this->sp));
}

const char *FuzzyControlView::getName()
{
    return "Fuzzy logic";
}

void FuzzyControlView::loadControlValues(std::string filepath) {

}
