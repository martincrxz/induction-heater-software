#ifndef FROM_FILE_CONTROL_VIEW_H
#define FROM_FILE_CONTROL_VIEW_H

#include <cstdint>
#include <QWidget>
#include <QDoubleValidator>
#include <vector>

#include "control_configuration.h"

namespace Ui {
class FromFileControlView;
}

class FromFileControlView: public ControlConfiguration
{
    Q_OBJECT

public:
    explicit FromFileControlView(QWidget *parent, SerialPort *sp);
    ~FromFileControlView();
    bool validateInput() override;
    void instantiate() override;
    const char * getName() override;
    void loadControlValues(std::string filepath = FILE_PATH) override;

private slots:
    void on_openFile_clicked();
    void on_saveButton_clicked();

private:
    Ui::FromFileControlView *ui;
    std::vector<std::vector<std::uint32_t>> controlDirectives;
    QDoubleValidator *kValidator;
    void parseFile();
};

#endif // FROM_FILE_CONTROL_VIEW_H
