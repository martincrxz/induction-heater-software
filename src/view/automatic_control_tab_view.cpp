#include "automatic_control_tab_view.h"
#include "ui_automatic_control_tab_view.h"
#include "control_configuration/classic_control_view.h"
#include "control_configuration/fuzzy_control_view.h"

AutomaticControlTabView::AutomaticControlTabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutomaticControlTabView)
{
    ui->setupUi(this);
    this->controlConfigViews.emplace_back(new ClassicControlView(this));
    this->controlConfigViews.emplace_back(new FuzzyControlView(this));
    this->current = ui->controlTypeCombo->currentIndex();
    ui->controlConfiguration->addWidget(this->controlConfigViews[this->current]);

    this->resetLabelTimer = new QTimer();
    connect(this->resetLabelTimer, &QTimer::timeout, this, 
        &AutomaticControlTabView::resetLabel);

    ui->warningLabel->setText("");
}

AutomaticControlTabView::~AutomaticControlTabView()
{
    delete ui;
    for (auto w: this->controlConfigViews) {
        delete w;
    }
}

void AutomaticControlTabView::on_controlTypeCombo_currentIndexChanged(int index)
{
    for (auto widget: this->controlConfigViews) {
        widget->hide();
    }

    ui->controlConfiguration->addWidget(this->controlConfigViews[index]);
    this->controlConfigViews[index]->show();
    this->current = index;
}

void AutomaticControlTabView::on_activateButton_clicked()
{
    bool isGood = this->controlConfigViews[this->current]->validateInput();
    if ( !isGood ) {
        ui->warningLabel->setText("Hay un error en los parámetros de control.");
        ui->warningLabel->setStyleSheet("QLabel { color : red; }");
        this->resetLabelTimer->start(3000);
    } 
}

void AutomaticControlTabView::resetLabel() {
    ui->warningLabel->setText("");
}
