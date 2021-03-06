#include <iostream>
#include <logger/logger.h>
#include "messages.h"

#include "application.h"
#include "exception.h"

bool Application::notify(QObject* receiver, QEvent* event)
{
    try {
        return QApplication::notify(receiver, event);
    } catch (std::exception &e) {
         Logger::critical(e.what());
         this->exit(1);
    } catch (...) {
         Logger::critical(UNKNOWN_ERROR_MSG, "Application");
         this->exit(1);
    }        
    return false;
}

Application::Application(int& argc, char** argv) :
    QApplication(argc, argv) {}