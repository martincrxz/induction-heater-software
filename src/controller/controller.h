class Controller {
public:
	Controller();
	~Controller();
	startChart();

private:
	std::thread chartUpdater;
}