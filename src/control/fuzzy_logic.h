
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */

#ifndef __FUZZY_LOGIC_H__
#define __FUZZY_LOGIC_H__

#define RULES_FILEPATH "./fuzzy_rules.txt"

#include <vector>
#include <string>

#include "classic_pid.h"
#include "MemberFunction.h"


class FuzzyLogic: public ClassicPID {
public:
    FuzzyLogic(float targetTemp, SerialPort *sp);
    virtual ~FuzzyLogic() override;
    virtual unsigned char process(std::shared_ptr<TemperatureReading> data) override;

private:
    /**
     * Actualiza los parametros kp kd y ki en función del error derivativo
     * y el error de la medicion.
     */
    void updateParameters(std::shared_ptr<TemperatureReading> data);
    std::vector<std::vector<std::string>> rules;
    std::vector<MemberFunction> input_member_func;
    std::vector<MemberFunction> output_member_func;
};


#endif // __FUZZY_LOGIC_H__
