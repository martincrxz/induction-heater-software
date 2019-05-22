#ifndef AUTOMATIC_CONTROL_TAB_VIEW_H
#define AUTOMATIC_CONTROL_TAB_VIEW_H

#include <QWidget>

namespace Ui {
class AutomaticControlTabView;
}

class AutomaticControlTabView : public QWidget
{
    Q_OBJECT

public:
    explicit AutomaticControlTabView(QWidget *parent = 0);
    ~AutomaticControlTabView();

private:
    Ui::AutomaticControlTabView *ui;
};

#endif // AUTOMATIC_CONTROL_TAB_VIEW_H
