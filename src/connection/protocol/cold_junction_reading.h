
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __cold_junction_reading_H__
#define __cold_junction_reading_H__

#include "micro_message.h"

class ColdJunctionReading: public MicroMessage {
public:
    ColdJunctionReading();
    virtual ~ColdJunctionReading() = default;
    QByteArray serialize() override;
};


#endif // __cold_junction_reading_H__
