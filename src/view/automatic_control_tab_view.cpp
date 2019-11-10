#include "automatic_control_tab_view.h"
#include "ui_automatic_control_tab_view.h"
#include "logger/logger.h"
#include "sstream"
AutomaticControlTabView::AutomaticControlTabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutomaticControlTabView)
{
    ui->setupUi(this);
//    this->controlViews.emplace_back(new ClassicControlView(this));
//    this->controlViews.emplace_back(new FuzzyControlView(this));
//    int current_index = ui->controlTypeCombo->currentIndex();
//    ui->controlConfiguration->addWidget(this->controlViews[current_index]);
    this->current = new ClassicControlView(this);
    ui->controlConfiguration->addWidget(current);
}

AutomaticControlTabView::~AutomaticControlTabView()
{
    delete ui;
    delete this->current;
}

void AutomaticControlTabView::on_controlTypeCombo_currentIndexChanged(int index)
{
	/**
	 *	Mi primer approach fue tener un vector de QWidgets *
	 *	donde creo una instancia de cada vista, y al cambiarse el combobox
	 *	hacía un remove widget y un add widget. Esto no funcionó, ya que
	 *	se glitchea la vista.
	 */ 
    ui->controlConfiguration->removeWidget(this->current);
    delete this->current;
    switch (index) {
    case 0:
    	Logger::info("Classic control selected");
        this->current = new ClassicControlView(this);
        break;
    case 1:
    	Logger::info("Fuzzy control selected")
        this->current = new FuzzyControlView(this);
        break;
    default:
        break;
    }
    ui->controlConfiguration->addWidget(this->current);
}
