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
    /**
     * @brief Habilita (o no) los botones de la vista. Se usa para evitar
     * envio de mensajes al micro que quieran controlar el horno cuando este
     * se encuentre en modo manual.
     * @param enable
     */
    void enableButtons(bool enable);

private:
    Ui::AutoTunningTabView *ui;
};

#endif // AUTO_TUNNING_TAB_VIEW_H
