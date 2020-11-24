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

#define ERROR_SENSITIVITY_DEFAULT_VALUE_2x1 900
#define ERROR_DERIVATIVE_SENSITIVITY_DEFAULT_VALUE_2x1 50
#define OUTPUT_SENSITIVITY_DEFAULT_VALUE_2x1 0.15

class Fuzzy2x1: public FuzzyLogic {
public:
    Fuzzy2x1(float targetTemp, SerialPort *sp, const std::string &filepath, uint8_t window_size,
            float errorS = ERROR_SENSITIVITY_DEFAULT_VALUE_2x1,
            float errorDerivativeS = ERROR_DERIVATIVE_SENSITIVITY_DEFAULT_VALUE_2x1,
            float outputS = OUTPUT_SENSITIVITY_DEFAULT_VALUE_2x1);
    virtual ~Fuzzy2x1() override;
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
    std::vector<MemberFunction> powerOutputFunctions;
    float power{0};
    float errorSensitivity;
    float errorDerivativeSensitivity;
    float outputSensitivity;
};


#endif // __FUZZY_3X1_H__
