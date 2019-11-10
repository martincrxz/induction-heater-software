#ifndef FUZZY_CONTROL_VIEW_H
#define FUZZY_CONTROL_VIEW_H

#include <QWidget>

namespace Ui {
class FuzzyControlView;
}

class FuzzyControlView : public QWidget
{
    Q_OBJECT

public:
    explicit FuzzyControlView(QWidget *parent = 0);
    ~FuzzyControlView();

private:
    Ui::FuzzyControlView *ui;
};

#endif // FUZZY_CONTROL_VIEW_H
