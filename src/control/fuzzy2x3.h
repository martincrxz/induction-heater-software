/*
 * Created by Federico Manuel Gomez Peter
 * on 23/7/2020.
 */
#ifndef __FUZZY_2X3_H__
#define __FUZZY_2X3_H__

#include <vector>
#include <string>

#include "fuzzy_logic.h"
#include "MemberFunction.h"

#define ERROR_SENSITIVITY_DEFAULT_VALUE_2x3 900
#define ERROR_DERIVATIVE_SENSITIVITY_DEFAULT_VALUE_2x3 50
#define KP_SENSITIVITY_DEFAULT_VALUE_2x3 0.15
#define KI_SENSITIVITY_DEFAULT_VALUE_2x3 0.15
#define KD_SENSITIVITY_DEFAULT_VALUE_2x3 0.15

class Fuzzy2x3: public FuzzyLogic {
public:
    Fuzzy2x3(float targetTemp, float kp, float kd, float ki,  SerialPort *sp, const std::string &filepath,
            uint8_t window_size, float errorS = ERROR_SENSITIVITY_DEFAULT_VALUE_2x3,
            float errorDerivativeS = ERROR_DERIVATIVE_SENSITIVITY_DEFAULT_VALUE_2x3,
            float kpS = KP_SENSITIVITY_DEFAULT_VALUE_2x3,
            float kiS = KI_SENSITIVITY_DEFAULT_VALUE_2x3,
            float kdS = KD_SENSITIVITY_DEFAULT_VALUE_2x3);
    virtual ~Fuzzy2x3() override;
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
    std::vector<MemberFunction> kpOutputFunctions;
    std::vector<MemberFunction> kiOutputFunctions;
    std::vector<MemberFunction> kdOutputFunctions;
    float errorSensitivity;
    float errorDerivativeSensitivity;
    float kpSensitivity;
    float kiSensitivity;
    float kdSensitivity;
    float initKp;
    float initKi;
    float initKd;
};


#endif // __FUZZY_2X3_H__
