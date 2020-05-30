
/*
 * Created by Federico Manuel Gomez Peter
 * on 28/5/20.
 */

#ifndef __MemberCandidate_H__
#define __MemberCandidate_H__

#include <string>

struct MemberCandidate {
    const float degree;
    const std::string &tag;

    MemberCandidate(float degree, const std::string &tag);
    ~MemberCandidate() = default;
};


#endif // __MemberCandidate_H__
