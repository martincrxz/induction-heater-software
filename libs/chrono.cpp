/*
 * Created by Federico Manuel Gomez Peter
 * on 25/06/19.
 */

#include <iomanip>
#include "chrono.h"

using _clock = std::chrono::system_clock;
using _duration = std::chrono::duration<double, std::milli>;

Chrono::Chrono(): start(_clock::now()) {}

double Chrono::tack() {
    auto current = _clock::now();
    return _duration(current - this->start).count();
}

void Chrono::tick() {
	this->start = _clock::now();
}

double Chrono::now() {
	std::chrono::time_point<_clock> tp = _clock::now();
	return _duration(tp.time_since_epoch()).count();
}

std::ostream &operator<<(std::ostream &os, Chrono &chrono) {
    os << std::fixed << std::setprecision(CHRONO_PRECISION) << chrono.now()
    << CHRONO_UNIT;
    return os;
}
