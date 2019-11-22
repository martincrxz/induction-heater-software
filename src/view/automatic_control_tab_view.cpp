#include "automatic_control_tab_view.h"
#include "ui_automatic_control_tab_view.h"
#include "control_configuration/classic_control_view.h"
#include "control_configuration/fuzzy_control_view.h"

#define ERROR 1

AutomaticControlTabView::AutomaticControlTabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutomaticControlTabView)
{
    ui->setupUi(this);
    auto classic_control = new ClassicControlView(this);
    this->controlConfigViews.emplace_back(classic_control);
    this->controlConfigViews.emplace_back(new FuzzyControlView(this));
    this->current = ui->controlTypeCombo->currentIndex();
    ui->controlConfiguration->addWidget(this->controlConfigViews[this->current]);

    this->resetLabelTimer = new QTimer();
    connect(this->resetLabelTimer, &QTimer::timeout, this, 
        &AutomaticControlTabView::resetLabel);
    connect(classic_control, &ClassicControlView::message,
            this, &AutomaticControlTabView::on_messagePrint);

    ui->warningLabel->setText("");
}

AutomaticControlTabView::~AutomaticControlTabView()
{
    delete ui;
    delete this->resetLabelTimer;
    for (auto w: this->controlConfigViews) {
        delete w;
    }
}

void AutomaticControlTabView::on_controlTypeCombo_currentIndexChanged(int index)
{
    for (auto widget: this->controlConfigViews) {
        widget->hide();
    }
    this->controlConfigViews[this->current]->stop();
    ui->controlConfiguration->addWidget(this->controlConfigViews[index]);
    this->controlConfigViews[index]->show();
    this->current = index;
}

void AutomaticControlTabView::on_activateButton_clicked()
{
    bool isGood = this->controlConfigViews[this->current]->validateInput();
    if ( !isGood ) {
        on_messagePrint("Hay un error en los parámetros de control.", ERROR);
    }
    this->controlConfigViews[this->current]->start();
}

void AutomaticControlTabView::on_messagePrint(const char *str, unsigned char mode)
{
    ui->warningLabel->setText(str);
    if (mode == ERROR){
        ui->warningLabel->setStyleSheet("QLabel { color : red; }");
    } else {
        ui->warningLabel->setStyleSheet("QLabel { color : green; }");
    }
    this->resetLabelTimer->start(3000);
}

void AutomaticControlTabView::resetLabel() {
    ui->warningLabel->setText("");
}

void AutomaticControlTabView::on_deactivateButton_clicked()
{
    this->controlConfigViews[this->current]->stop();
}
