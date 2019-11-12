#include "classic_control_view.h"
#include "ui_classic_control_view.h"

ClassicControlView::ClassicControlView(QWidget *parent) :
    ControlConfiguration(parent),
    ui(new Ui::ClassicControlView)
{
    ui->setupUi(this);
    ui->kd_valjue->setValidator(new QDoubleValidator(-9999, 9999, 2));
    ui->ki_value->setValidator(new QDoubleValidator(-9999, 9999, 2));
    ui->kp_value->setValidator(new QDoubleValidator(-9999, 9999, 2));
}

ClassicControlView::~ClassicControlView()
{
    delete ui;
}

bool ClassicControlView::validateInput()
{
    QString kd = ui->kd_valjue->text();
    QString ki = ui->ki_value->text();
    QString kp = ui->kp_value->text();
    int d = 0;
    auto validator = ui->kd_valjue->validator();
    auto kdState = validator->validate(kd, d);
    auto kiState = validator->validate(ki, d);
    auto kpState = validator->validate(kp, d);

    if ( kdState != QValidator::Acceptable ||
         kiState != QValidator::Acceptable ||
         kpState != QValidator::Acceptable ) {
        return false;
    }

    return true;
}
