#include <exception>
#include <iostream>
#include <QApplication>
#include <logger/logger_worker.h>
#include <logger/logger.h>

#include "exception.h"
#include "view/application.h"
#include "view/general_view.h"

int main(int argc, char *argv[])
{	
	int ret = 0;
	try {
    	Application a(argc, argv);
        Logger::init();
    	MainWindow w;
		w.show();

		ret = a.exec();
	} catch (std::exception &e) {
		Logger::critical(e.what());
		return 1;
	} catch (...) {
		Logger::critical("Unknown error on main thread.");
		return 1;
	}
	return ret;
}
