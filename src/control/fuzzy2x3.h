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

class Fuzzy2x3: public FuzzyLogic {
public:
    Fuzzy2x3(float targetTemp, float deadzone, float kp, float kd, float ki,  SerialPort *sp, const std::string &filepath,
            uint8_t window_size, float errorS, float errorDerivativeS, float kpS, float kiS, float kdS);
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
