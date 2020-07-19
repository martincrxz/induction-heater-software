#include "fuzzy_control_view.h"
#include "ui_fuzzy_control_view.h"

#include "../../control/fuzzy_logic.h"

FuzzyControlView::FuzzyControlView(QWidget *parent, SerialPort *s) :
    ControlConfiguration(parent, s),
    ui(new Ui::FuzzyControlView)
{
    ui->setupUi(this);
    ui->helpbutton->setToolTip("<b>Ayuda:</b><br>"
                               "El modo de operación '2x3' toma el error de temperatura "
                               "y la derivada del error para modificar los valores "
                               "de las constantes kp, kd y ki del control PID clásico. "
                               "Se debe brindar obligatoriamente valores iniciales de "
                               "estas constantes.<br>"
                               "El modo de operación '3x1' toma como entradas "
                               "la temperatura, la derivada y la integral de estas, y "
                               "se actua sobre la potencia de salida.");
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

void FuzzyControlView::on_operationModeCombo_currentIndexChanged(int index)
{
    // Si selecciono un modo que no sea 3 salidas (las constantes de
    // control clásico) entonces oculto los line edit de las constantes
    // iniciales.
    if (index) {
        this->ui->kdLabel->hide();
        this->ui->kpLabel->hide();
        this->ui->kiLabel->hide();
        this->ui->kdLineEdit->hide();
        this->ui->kpLineEdit->hide();
        this->ui->kILineEdit->hide();
    } else {
        this->ui->kdLabel->show();
        this->ui->kpLabel->show();
        this->ui->kiLabel->show();
        this->ui->kdLineEdit->show();
        this->ui->kpLineEdit->show();
        this->ui->kILineEdit->show();
    }
}
