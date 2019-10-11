#ifndef EQUIPMENT_STATUS_VIEW_H
#define EQUIPMENT_STATUS_VIEW_H

#include <QWidget>

namespace Ui {
class EquipmentStatusView;
}

class EquipmentStatusView : public QWidget
{
    Q_OBJECT

public:
    explicit EquipmentStatusView(QWidget *parent = 0);
    ~EquipmentStatusView();
    void insert(QString, QString, QString);

private:
    Ui::EquipmentStatusView *ui;
};

#endif // EQUIPMENT_STATUS_VIEW_H
