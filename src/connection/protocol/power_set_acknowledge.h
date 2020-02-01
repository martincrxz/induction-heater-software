
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __POWER_SET_ACKNOWLEDGE_H__
#define __POWER_SET_ACKNOWLEDGE_H__

#define MINIMUM_TAP 0   // potencia maxima (100%)
#define MAXIMUM_TAP 127 // potencia minima (0%)

#include <cstdint>

#include "incoming_message.h"

class PowerSetAcknowledge: public IncomingMessage {
private:
    std::uint8_t data;
public:
    PowerSetAcknowledge(QByteArray &);
    virtual ~PowerSetAcknowledge() = default;
    float getPower();
};


#endif // __POWER_SET_ACKNOWLEDGE_H__
