#include <exception>
#include <iostream>
#include <QApplication>

#include "exception.h"
#include "view/application.h"
#include "view/general_view.h"


int main(int argc, char *argv[])
{	
	int ret = 0;
	try {
    	qputenv("QT_STYLE_OVERRIDE","");
    	Application a(argc, argv);
    	MainWindow w;
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
