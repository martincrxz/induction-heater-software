#ifndef __CHART_CONF_H__
#define __CHART_CONF_H__

#include <cstdint>

struct AxisConfiguration {
    const char         *name;
    const char         *type;
    const std::uint64_t min;
    const std::uint64_t max;

    AxisConfiguration();
    AxisConfiguration(const char *name, const char *type, std::uint64_t min,
        std::uint64_t max);
    ~AxisConfiguration() = default;
};

struct ChartConfiguration {
    const AxisConfiguration   yaxis1;
    const AxisConfiguration   yaxis2;
    const AxisConfiguration   xaxis;
    const char*               title;

    ChartConfiguration(AxisConfiguration &xaxis, AxisConfiguration &yaxis1,
        const char *title);
    ChartConfiguration(AxisConfiguration &xaxis, AxisConfiguration &yaxis1, 
        AxisConfiguration &yaxis2, const char *title);
    ~ChartConfiguration() = default;
};

#endif