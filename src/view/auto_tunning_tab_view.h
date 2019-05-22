#ifndef AUTO_TUNNING_TAB_VIEW_H
#define AUTO_TUNNING_TAB_VIEW_H

#include <QWidget>

namespace Ui {
class AutoTunningTabView;
}

class AutoTunningTabView : public QWidget
{
    Q_OBJECT

public:
    explicit AutoTunningTabView(QWidget *parent = 0);
    ~AutoTunningTabView();

private:
    Ui::AutoTunningTabView *ui;
};

#endif // AUTO_TUNNING_TAB_VIEW_H
