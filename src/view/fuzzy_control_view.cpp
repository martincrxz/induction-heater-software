#include "fuzzy_control_view.h"
#include "ui_fuzzy_control_view.h"

FuzzyControlView::FuzzyControlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FuzzyControlView)
{
    ui->setupUi(this);
}

FuzzyControlView::~FuzzyControlView()
{
    delete ui;
}
