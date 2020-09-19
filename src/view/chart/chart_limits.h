#ifndef __CHART_LIMITS_H__
#define __CHART_LIMITS_H__

#include <QtCore/QDateTime>

struct ChartLimits {
	QDateTime	time_min;
	QDateTime 	time_max;
	double 		y1_min;
	double 		y1_max;
	double 		y2_min;
	double 		y2_max;
	double		y3_min;
	double		y3_max;
	double		y4_min;
	double		y4_max;

	ChartLimits(QDateTime &time_min, QDateTime &time_max, double y1_min,
		double y1_max,	double y2_min, double y2_max, double y3_min, double y3_max,
		double y4_min, double y4_max): time_min(time_min),
				time_max(time_max), y1_min(y1_min), y1_max(y1_max),
				y2_min(y2_min), y2_max(y2_max),
				y3_min(y3_min), y3_max(y3_max),
				y4_min(y4_min), y4_max(y4_max) {}
	ChartLimits(ChartLimits &&other): time_min(std::move(other.time_min)),
				time_max(std::move(other.time_max)), y1_min(other.y1_min), 
				y1_max(other.y1_max), y2_min(other.y2_min), 
				y2_max(other.y2_max),
				y3_min(other.y3_min), y3_max(other.y3_max),
				y4_min(other.y4_min), y4_max(other.y4_max) {
		other.y1_max = 0;
		other.y1_min = 0;
		other.y2_max = 0;
		other.y2_min = 0;
		other.y3_min = 0;
		other.y3_max = 0;
		other.y4_min = 0;
		other.y4_max = 0;
	}

	ChartLimits & operator=(ChartLimits &&other) {
		if (this == &other) {
			return *this;
		}

		this->y1_max = other.y1_max;
		this->y1_min = other.y1_min;
		this->y2_max = other.y2_max;
		this->y2_min = other.y2_min;
		this->y3_max = other.y3_max;
		this->y3_min = other.y3_min;
		this->y4_max = other.y4_max;
		this->y4_min = other.y4_min;
		this->time_max = std::move(other.time_max);
		this->time_min = std::move(other.time_min);
		other.y1_max = 0;
		other.y1_min = 0;
		other.y2_max = 0;
		other.y2_min = 0;
		other.y3_max = 0;
		other.y3_min = 0;
		other.y4_max = 0;
		other.y4_min = 0;
		return *this;
	}

	ChartLimits(ChartLimits &copy) = delete;
	ChartLimits & operator=(const ChartLimits &cpy) = delete;
};

#endif