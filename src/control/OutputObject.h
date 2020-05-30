
/*
 * Created by Federico Manuel Gomez Peter
 * on 28/5/20.
 */

#ifndef __OutputObject_H__
#define __OutputObject_H__


#include <vector>
#include <string>

#include "MemberCandidate.h"
#include "MemberFunction.h"

class OutputObject {
    std::vector<MemberCandidate> candidates;
public:
    OutputObject() = default;
    ~OutputObject() = default;
    void emplace(float degree, const std::string &tag);
    float calculate_delta(const std::vector<MemberFunction> &functions) const;
};


#endif // __OutputObject_H__
