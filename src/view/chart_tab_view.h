#ifndef CHART_TAB_VIEW_H
#define CHART_TAB_VIEW_H

#include <QWidget>

namespace Ui {
class ChartTabView;
}

class ChartTabView : public QWidget
{
    Q_OBJECT

public:
    explicit ChartTabView(QWidget *parent = 0);
    ~ChartTabView();

private:
    Ui::ChartTabView *ui;
};

#endif // CHART_TAB_VIEW_H
