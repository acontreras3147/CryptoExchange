/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Producer.h defines Producer's members, including service routine, Buffer, and Synch
 */

#ifndef PRODUCER_H
#define PRODUCER_H

#include "Service.h"
#include "Buffer.h"
#include "Synch.h"

class ProducerData {
public:
    ProducerData(TradeRequestService service, Buffer* buffer, Synch* synch);

    TradeRequestService service; Buffer* buffer; Synch* synch;
};

void* produce(void* arg);

#endif //PRODUCER_H
