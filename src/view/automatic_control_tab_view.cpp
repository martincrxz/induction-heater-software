#include "automatic_control_tab_view.h"
#include "ui_automatic_control_tab_view.h"
#include "control_configuration/classic_control_view.h"
#include "control_configuration/fuzzy_control_view.h"
#include "control_configuration/from_file_control_view.h"

#define ERROR 1

AutomaticControlTabView::AutomaticControlTabView(QWidget *parent,
                                                 SerialPort *pPort) :
    QWidget(parent),
    ui(new Ui::AutomaticControlTabView),
    port(pPort)
{
    ui->setupUi(this);
    fillControlConfigViews();
    this->current = ui->controlTypeCombo->currentIndex();

    this->resetLabelTimer = new QTimer();
    connect(this->resetLabelTimer, &QTimer::timeout, this, 
        &AutomaticControlTabView::resetLabel);
    for (auto controlView : this->controlConfigViews) {
        ui->controlConfiguration->addWidget(controlView);
        connect(controlView, &ControlConfiguration::message,
            this, &AutomaticControlTabView::on_messagePrint);
    }
    this->on_controlTypeCombo_currentIndexChanged(this->current);
    ui->warningLabel->setText("");
}

AutomaticControlTabView::~AutomaticControlTabView()
{
    delete ui;
    this->resetLabelTimer->stop();
    delete this->resetLabelTimer;
    for (auto w: this->controlConfigViews) {
        delete w;
    }
}

void AutomaticControlTabView::on_controlTypeCombo_currentIndexChanged(int index)
{
    std::lock_guard<std::recursive_mutex> lock(this->mutex);
    for (auto widget: this->controlConfigViews) {
        widget->hide();
    }
    this->controlConfigViews[index]->show();
    this->current = index;
}

void AutomaticControlTabView::on_activateButton_clicked()
{
    std::lock_guard<std::recursive_mutex> lock(this->mutex);
    if (!isControlActivated()) {
        bool isGood = this->controlConfigViews[this->current]->validateInput();
        if ( !isGood ) {
            on_messagePrint("Hay un error en los parámetros de control.", ERROR);
            return;
        }
        this->controlConfigViews[this->current]->start();
        activatedControlAlgorithmIndex = this->current;
        on_messagePrint("Se activó el proceso de control correctamente", OK);
        emit controlAlgorithmActivated();
    } else {
        on_messagePrint("Hay un proceso activo.", ERROR);
    }
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
    std::lock_guard<std::recursive_mutex> lock(this->mutex);
    if (isControlActivated()){
        this->controlConfigViews[this->activatedControlAlgorithmIndex]->stop();
        activatedControlAlgorithmIndex = -1;
        on_messagePrint("Proceso detenido correctamente", OK);
        emit controlAlgorithmDeactivated();
    } else {
        on_messagePrint("No hay proceso que desactivar", ERROR);
    }
}

void AutomaticControlTabView::dataAvailable(TemperatureReading &temp) {
    std::lock_guard<std::recursive_mutex> lock(this->mutex);
    this->controlConfigViews[this->current]->dataAvailable(temp);
}

void AutomaticControlTabView::enableButtons(bool enable) {
    this->ui->deactivateButton->setEnabled(enable);
    this->ui->activateButton->setEnabled(enable);
}

void AutomaticControlTabView::fillControlConfigViews() {
    auto classic_control = new ClassicControlView(this, this->port);
    this->controlConfigViews.emplace_back(classic_control);
    this->controlConfigViews.emplace_back(new FuzzyControlView(this, this->port));
    this->controlConfigViews.emplace_back(new FromFileControlView(this, this->port));
    for (auto widget : this->controlConfigViews) {
        ui->controlTypeCombo->addItem(widget->getName());
    }
}

bool AutomaticControlTabView::isControlActivated() {
    std::lock_guard<std::recursive_mutex> lock(this->mutex);
    return activatedControlAlgorithmIndex >= 0;
}

void AutomaticControlTabView::loadFile(std::string file_path) {
    for (auto view : this->controlConfigViews) {
        view->loadControlValues(file_path);
    }
}
