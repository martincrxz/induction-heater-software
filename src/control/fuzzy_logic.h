
/*
 * Created by Federico Manuel Gomez Peter
 * on 20/5/20.
 */

#ifndef __FUZZY_LOGIC_H__
#define __FUZZY_LOGIC_H__

#include <vector>
#include <string>

#include "classic_pid.h"
#include "MemberFunction.h"

#define JSON_FILEPATH "fuzzy/fuzzy2x3.json"
#define JSON_BUFFER_SIZE 4 * 1024

class FuzzyLogic: public ClassicPID {
public:
    FuzzyLogic(float targetTemp, SerialPort *sp, const std::string &filepath, uint8_t window_size);
    virtual ~FuzzyLogic() override;
    virtual unsigned char process(std::shared_ptr<TemperatureReading> data) override;

private:
    /**
     * Actualiza los parametros kp kd y ki en función del error derivativo
     * y el error de la medicion.
     */
    void loadJson(const std::string &filepath);
    void loadFunctions(std::vector<MemberFunction>& holder, QJsonObject &document,
            const std::string functionType, const std::string id);
    void updateParameters(std::shared_ptr<TemperatureReading> data);
    /**
     * @brief  Imprime la configuración del control (loggeando en debug)
     */
    void printConf() const;
    std::vector<std::vector<std::string>> rules;
    std::vector<MemberFunction> errorMemberFunctions;
    std::vector<MemberFunction> errorDerivativeMemberFunctions;
    std::vector<MemberFunction> kpOutputFunctions;
    std::vector<MemberFunction> kiOutputFunctions;
    std::vector<MemberFunction> kdOutputFunctions;
};


#endif // __FUZZY_LOGIC_H__
