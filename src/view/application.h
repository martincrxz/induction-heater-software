#include <QApplication>

class Application : public QApplication {
public:
    Application(int& argc, char** argv);
    bool notify(QObject* receiver, QEvent* event); 
};