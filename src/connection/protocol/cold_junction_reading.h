
/*
 * Created by Federico Manuel Gomez Peter
 * on 13/10/19.
 */

#ifndef __cold_junction_reading_H__
#define __cold_junction_reading_H__

#include "incoming_message.h"

class ColdJunctionReading: public IncomingMessage {
private:
    float data;
public:
    ColdJunctionReading(QByteArray &);
    virtual ~ColdJunctionReading() = default;
    float getData();
};


#endif // __cold_junction_reading_H__
