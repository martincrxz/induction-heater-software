/*
 * Created by Federico Manuel Gomez Peter
 * on 27/7/2020.
 */
#ifndef __FUZZY_3X1_H__
#define __FUZZY_3X1_H__

#include <vector>
#include <string>

#include "fuzzy_logic.h"
#include "MemberFunction.h"

class Fuzzy3x1: public FuzzyLogic {
public:
    Fuzzy3x1(float targetTemp, SerialPort *sp, const std::string &filepath, uint8_t window_size);
    virtual ~Fuzzy3x1() override;
    virtual unsigned char process(std::shared_ptr<TemperatureReading> data) override;
protected:
    virtual void loadMemberFunctions(QJsonObject& document) override;
    /**
     * @brief  Imprime la configuración del control (loggeando en debug)
     */
    void printConf() const override;
private:
    void updateParameters(std::shared_ptr<TemperatureReading> data);
    std::vector<MemberFunction> errorMemberFunctions;
    std::vector<MemberFunction> errorDerivativeMemberFunctions;
    std::vector<MemberFunction> errorIntegralMemberFunctions;
    std::vector<MemberFunction> powerOutputFunctions;
    float power{0};
};


#endif // __FUZZY_3X1_H__
