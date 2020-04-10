AxisConfiguration::AxisConfiguration(): name(nullptr), type(nullptr), min(0),
		max(0) {}

AxisConfiguration::AxisConfiguration(const char *name, const char *type, 
		std::uint64_t min, std::uint64_t max): name(name), type(type), min(min),
			max(max) {}

ChartConfiguration::ChartConfiguration(AxisConfiguration &xaxis,
	AxisConfiguration &yaxis1, const char *title): yaxis1(yaxis1), yaxis2(), 
			xaxis(xaxis), title(title) {}

ChartConfiguration::ChartConfiguration(AxisConfiguration &xaxis, 
	AxisConfiguration &yaxis1, AxisConfiguration &yaxis2, const char *title):
		yaxis1(yaxis1), yaxis2(yaxis2), xaxis(xaxis), title(title) {}