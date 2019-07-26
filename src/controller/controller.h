#include <thread>

class Controller {
public:
	Controller();
	~Controller();
	void startChart();

private:
	std::thread chartUpdater;
};