
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __thermocouple_fault_H__
#define __thermocouple_fault_H__


#include "micro_message.h"

typedef enum {CJRANGE_FAULT = 0x80,
              TCRANGE_FAULT = 0x40,
              CJHIGH_FAULT = 0x20,
              CJLOW_FAULT = 0x10,
              TCHIGH_FAULT = 0x08,
              TCLOW_FAULT = 0x04,
              OVUV_FAULT = 0x02,
              OPEN_FAULT = 0x01
} thermocouple_fault_t;

class ThermocoupleFault: public MicroMessage {
private:
    thermocouple_fault_t fault;
public:
    explicit ThermocoupleFault(QByteArray buff);
    virtual ~ThermocoupleFault() = default;
    QByteArray serialize() override;
    QString error();
};


#endif // __thermocouple_fault_H__
