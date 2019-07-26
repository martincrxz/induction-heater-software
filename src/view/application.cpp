#include <iostream>

#include "application.h"
#include "exception.h"

bool Application::notify(QObject* receiver, QEvent* event)
{
    try {
        return QApplication::notify(receiver, event);
    } catch (std::exception &e) {
         Exception e1("Error: %s.\nSending event %s to object %s (%s)",
            e.what(), typeid(*event).name(), 
            qPrintable(receiver->objectName()), 
            typeid(*receiver).name());
         std::cerr << e1.what() << std::endl;
         this->exit(1);
    } catch (...) {
		 Exception e("Unknown error sending event %s to object %s (%s)", 
            typeid(*event).name(), qPrintable(receiver->objectName()),
            typeid(*receiver).name());
         std::cerr << e.what() << std::endl;
         this->exit(1);
    }        
    return false;
}

Application::Application(int& argc, char** argv) :
    QApplication(argc, argv) {}