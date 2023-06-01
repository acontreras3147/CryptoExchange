/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Consumer.h defines Consumer's members, including service routine, Buffer, and Synch
 */

#ifndef CONSUMER_H
#define CONSUMER_H

#include "Service.h"
#include "Buffer.h"
#include "Synch.h"
#include "log.h"

class ConsumerData {
public:
    ConsumerData(RequestTransactionService service, Buffer* buffer, Synch* synch);

    RequestTransactionService service; Buffer* buffer; Synch* synch;
};

void* consume(void* arg);

#endif //CONSUMER_H
