#include "messages.h"
#include "automatic_control_tab_view.h"
#include "general_view.h"
#include "ui_automatic_control_tab_view.h"
#include "control_configuration/classic_control_view.h"
#include "control_configuration/fuzzy_control_view.h"
#include "control_configuration/from_file_control_view.h"
#include "message_modes.h"
#include "logger/logger.h"

AutomaticControlTabView::AutomaticControlTabView(QWidget *parent,
                                                 SerialPort *pPort) :
    QWidget(parent),
    ui(new Ui::AutomaticControlTabView),
    port(pPort)
{
    ui->setupUi(this);
    fillControlConfigViews();
    this->current = ui->controlTypeCombo->currentIndex();

    for (auto controlView : this->controlConfigViews) {
        ui->controlConfiguration->addWidget(controlView);
        connect(controlView, &ControlConfiguration::message,
            (MainWindow *) parent, &MainWindow::on_messagePrint);
    }
    this->on_controlTypeCombo_currentIndexChanged(this->current);
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
    try {
        if (!isControlActivated()) {
        bool isGood = this->controlConfigViews[this->current]->validateInput();
        if ( !isGood ) {
            emit printMessage(AUTOMATIC_CONTROL_VIEW_BAD_ARGUMENTS_ERROR_MSG, ERROR, true);
            return;
        }
            this->controlConfigViews[this->current]->start();
            activatedControlAlgorithmIndex = this->current;
            emit printMessage(AUTOMATIC_CONTROL_VIEW_PROCESS_ACTIVATED_MSG, OK, true);
            emit controlAlgorithmActivated();
        } else {
            emit printMessage(AUTOMATIC_CONTROL_VIEW_PROCESS_ACTIVE_ERROR_MSG, ERROR, true);
        }
    } catch (std::exception &e) {
        Logger::warning(e.what());
        emit printMessage(e.what(), ERROR, true);
    }
}

void AutomaticControlTabView::on_deactivateButton_clicked()
{
    stop(true);
}

void AutomaticControlTabView::stop(bool printError) {
    std::lock_guard<std::recursive_mutex> lock(this->mutex);
    if (isControlActivated()){
        this->controlConfigViews[this->activatedControlAlgorithmIndex]->stop();
        activatedControlAlgorithmIndex = -1;
        emit printMessage(AUTOMATIC_CONTROL_PROCESS_DEACTIVATED_MSG, OK, true);
        emit controlAlgorithmDeactivated();
    } else if (printError) {
        emit printMessage(AUTOMATIC_CONTROL_VIEW_NO_PROCESS_ACTIVE_MSG, ERROR, true);
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

const char *AutomaticControlTabView::getProcessName()
{
    std::lock_guard<std::recursive_mutex> lock(this->mutex);
    if (isControlActivated())
        return this->controlConfigViews[this->current]->getName();
    else
        return "-";
}

void AutomaticControlTabView::updateConfig() {
  for (auto controlView : this->controlConfigViews) {
    controlView->updateConfig();
  }
}