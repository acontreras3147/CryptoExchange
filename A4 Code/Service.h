/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Service.h defines service routine members, including RequestTransaction array to track consumption
 */

#ifndef SERVICE_H
#define SERVICE_H

#include "cryptoexchange.h"

#define MILLI_TO_MICRO 1000

struct TradeRequestService {
    TradeRequestService(RequestType type);

    RequestType type;
    int processing_time = 0;
};

struct RequestTransactionService {
    RequestTransactionService(ConsumerType type);

    ConsumerType type;
    int processing_time = 0;

    // Array tracking service's consumption of each type of request
    // Indices: BTC = 0, ETH = 1
    unsigned int reqs_consumed[2] = {0};
};



#endif // SERVICE_H
