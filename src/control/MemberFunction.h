
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */

#ifndef __MemberFuntion_H__
#define __MemberFuntion_H__

#include <string>

class MemberFunction {
private:
    // puntos de un trapecio
    float a;
    float b;
    float c;
    float d;
    // centro de masa (eje X)
    float center{0};
    std::string tag;

public:
    // Pre: a <= b <= c <= d
    MemberFunction(float a, float b, float c, float d, std::string tag);
    ~MemberFunction() = default;
    // calcula el valor de una función trapezoidal que
    //  * para x < a vale 0,
    //  * x entre a y b vale una recta de pendiente positiva,
    //  * x entre b y c => 1
    //  * x > c => 0
    float calculate(float x);
    const std::string & getTag() const;
    float getCenter() const;
};


#endif // __MemberFuntion_H__
