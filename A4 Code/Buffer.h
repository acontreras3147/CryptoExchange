/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Buffer.h defines Buffer's members, including a queue and mutex related to process synchronization
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <queue>
#include <pthread.h>
#include "Request.h"
#include "Synch.h"
#include "Service.h"
extern "C" {
#include "log.h"
};

using namespace std;

class Buffer {
public:
    Buffer(int prod_limit);

    int prod_limit;
    pthread_mutex_t mutex;
    queue<Request> trade_req_queue;

    // Arrays tracking reqs produced and reqs within queue
    // Indices: BTC = 0, ETH = 1
    unsigned int reqs_produced[2] = {0};
    unsigned int queue_tracker[2] = {0};

    void publish(TradeRequestService* service, Request req);
    Request retrieve(RequestTransactionService* service, sem_t* barrier);
    bool isEmpty();
    int getProductionSum();
};


#endif //BUFFER_H
