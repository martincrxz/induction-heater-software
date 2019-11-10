#ifndef CLASSIC_CONTROL_VIEW_H
#define CLASSIC_CONTROL_VIEW_H

#include <QWidget>

namespace Ui {
class ClassicControlView;
}

class ClassicControlView : public QWidget
{
    Q_OBJECT

public:
    explicit ClassicControlView(QWidget *parent = 0);
    ~ClassicControlView();

private:
    Ui::ClassicControlView *ui;
};

#endif // CLASSIC_CONTROL_VIEW_H
