
/*
 * Created by Federico Manuel Gomez Peter
 * on 28/5/20.
 */

#include "OutputObject.h"

void OutputObject::emplace(float degree, const std::string &tag) {
    this->candidates.emplace_back(degree, tag);
}
/**
 * Calcula el delta a aumentar como un promedio ponderado por el degree
 * entre los distintos candidatos
 */
float OutputObject::calculate_delta(
        const std::vector<MemberFunction> &functions) const{
    const MemberFunction *function;
    float ret = 0;
    float divisor = 0;
    for (auto &candidate : this->candidates){
        divisor += candidate.degree;
        for (auto &f : functions) {
            if (f.getTag() == candidate.tag) {
                ret += f.getCenter() * candidate.degree;
            }
        }
    }
    return ret / divisor;
}
