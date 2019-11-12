#ifndef __CONTROL_CONFIGURATION_H__
#define __CONTROL_CONFIGURATION_H__

#include <QWidget>

class ControlConfiguration : public QWidget
{
    Q_OBJECT
public:
    explicit ControlConfiguration(QWidget *parent = nullptr);
    virtual bool validateInput() = 0;
signals:

public slots:
};

#endif // __CONTROL_CONFIGURATION_H__
