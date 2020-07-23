
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */

#include <exception.h>
#include <sstream>

#include "logger/logger.h"
#include "MemberFunction.h"

MemberFunction::MemberFunction(float a, float b, float c, float d, std::string tag):
    a(a), b(b), c(c), d(d), tag(tag) {
    if (a > b || b > c || c > d) {
        throw Exception("Se debe cumplir que a (%f) <= b (%f)"
                        "<= c (%f) <= d (%f)", a, b, c, d);
    }
    // TODO: esta formual vale porque definimos las member functions simétricas.
    // reveer esto.
    this->center = (d - a) / 2;

}

float MemberFunction::calculate(float x) {
    if (x >= a && x <= b) {
        if (b == a)
            return 1;
        else
            return (x - a) / (b - a);
    }

    else if (x >= b && x <= c) {
        return 1;
    }

    else if (x >= c && x <= d) {
        if (d == c)
            return 1;
        else
            return (d - x) / (d - c);
    }
    else
        return 0;
}

const std::string &MemberFunction::getTag() const {
    return this->tag;
}

float MemberFunction::getCenter() const {
    return this->center;
}

void MemberFunction::print() const {
    std::ostringstream oss;
    oss << this->tag << ": [" << a << ", " << b << ", " << c << ", " << d 
        << "]";
    Logger::debug(oss.str().c_str());
}