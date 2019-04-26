#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_STYLE_OVERRIDE","");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
