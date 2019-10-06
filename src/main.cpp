#include <exception>
#include <iostream>
#include <QApplication>
#include <logger/logger_worker.h>
#include <logger/logger.h>

#include "exception.h"
#include "view/application.h"
#include "view/general_view.h"
#include "connection/communicator.h"

#define PRINT(X) std::cout<<X<<std::endl

int main(int argc, char *argv[])
{	
	int ret = 0;
	try {
    	Application a(argc, argv);
    	MainWindow w;
        Logger::init("filename");
        w.show();
        ret = a.exec();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} catch (...) {
		Exception e("Unknown error un thread main.");
		std::cerr << e.what() << std::endl;
		return 1;
	}
    return ret;
}
