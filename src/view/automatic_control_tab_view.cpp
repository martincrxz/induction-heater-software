#include "automatic_control_tab_view.h"
#include "ui_automatic_control_tab_view.h"
#include "control_configuration/classic_control_view.h"
#include "control_configuration/fuzzy_control_view.h"

#define ERROR 1

AutomaticControlTabView::AutomaticControlTabView(QWidget *parent,
                                                 SerialPort *pPort) :
    QWidget(parent),
    ui(new Ui::AutomaticControlTabView),
    port(pPort)
{
    ui->setupUi(this);
    this->tempValidator = new QDoubleValidator(-99999, 99999, 2);
    this->ui->targetTemperatureTextEdit->setValidator(this->tempValidator);
    auto classic_control = new ClassicControlView(this, this->port, this->tempValidator);
    this->controlConfigViews.emplace_back(classic_control);
    this->controlConfigViews.emplace_back(new FuzzyControlView(this, this->port, this->tempValidator));
    this->current = ui->controlTypeCombo->currentIndex();
    ui->controlConfiguration->addWidget(this->controlConfigViews[this->current]);

    this->resetLabelTimer = new QTimer();
    connect(this->resetLabelTimer, &QTimer::timeout, this, 
        &AutomaticControlTabView::resetLabel);
    connect(classic_control, &ClassicControlView::message,
            this, &AutomaticControlTabView::on_messagePrint);

    ui->warningLabel->setText("");
    this->enableButtons(false);
}

AutomaticControlTabView::~AutomaticControlTabView()
{
    delete ui;
    this->resetLabelTimer->stop();
    delete this->resetLabelTimer;
    delete this->tempValidator;
    for (auto w: this->controlConfigViews) {
        delete w;
    }
}

void AutomaticControlTabView::on_controlTypeCombo_currentIndexChanged(int index)
{
    std::lock_guard<std::mutex> lock(this->mutex);
    for (auto widget: this->controlConfigViews) {
        widget->hide();
    }
    // TODO: esto no me gusta acá, debería stoppearse el antiguo hilo de control
    // cuando se active el nuevo.
    this->controlConfigViews[this->current]->stop();
    ui->controlConfiguration->addWidget(this->controlConfigViews[index]);
    this->controlConfigViews[index]->show();
    this->current = index;
}

void AutomaticControlTabView::on_activateButton_clicked()
{
    std::lock_guard<std::mutex> lock(this->mutex);
    QString targetTempStr = this->ui->targetTemperatureTextEdit->text();
    bool isGood = this->controlConfigViews[this->current]->validateInput(&targetTempStr);
    // TODO: agregar validador del textinput.
    float targetTemp = targetTempStr.toFloat();
    if ( !isGood ) {
        on_messagePrint("Hay un error en los parámetros de control.", ERROR);
        return;
    }
    this->controlConfigViews[this->current]->start(targetTemp);
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
    std::lock_guard<std::mutex> lock(this->mutex);
    this->controlConfigViews[this->current]->stop();
}

void AutomaticControlTabView::dataAvailable(TemperatureReading &temp) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->controlConfigViews[this->current]->dataAvailable(temp);
}

void AutomaticControlTabView::enableButtons(bool enable) {
    this->ui->deactivateButton->setEnabled(enable);
    this->ui->activateButton->setEnabled(enable);
}
