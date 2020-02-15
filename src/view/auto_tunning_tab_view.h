#ifndef AUTO_TUNNING_TAB_VIEW_H
#define AUTO_TUNNING_TAB_VIEW_H

#include <QWidget>

namespace Ui {
class AutoTunningTabView;
}

class MainWindow;

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

public slots:
    void activate();

private:
    Ui::AutoTunningTabView *ui;
    MainWindow* mainWindow;
};

#endif // AUTO_TUNNING_TAB_VIEW_H
