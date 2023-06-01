/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Buffer.cpp implements exclusive access methods for modifying the queue and checking its status
 */

#include "Buffer.h"

/**
 * Buffer constructor, initializes mutex & tracks production limit
 * @param prod_limit                    Production limit
 */
Buffer::Buffer(int prod_limit) {
    pthread_mutex_init(&this->mutex, nullptr);
    this->prod_limit = prod_limit;
}

/**
 * publish() implements Producer threads' critical section for pushing requests onto queue. Logs additions and
 * implements check on production limit for exiting.
 * @param service                       Service routine producing trade requests
 * @param req                           Request to be added
 */
void Buffer::publish(TradeRequestService* service, Request req) {
    pthread_mutex_lock(&this->mutex); // START of Critical Section

    // Check if prod. limit reached
    if (getProductionSum() >= prod_limit) { // Exit thread!
        pthread_mutex_unlock(&this->mutex);
        pthread_exit(nullptr);
    }

    // Push request onto queue
    this->trade_req_queue.push(req);

    // Update values tracking reqs produced & reqs in queue
    this->reqs_produced[req.idx]++;
    this->queue_tracker[req.idx]++;

    // Log addition
    log_request_added(service->type,
                      reqs_produced, queue_tracker);

    pthread_mutex_unlock(&this->mutex); // END of Critical Section
}

/**
 * retrieve() implements Consumer threads' critical section for popping requests off the queue. Logs removals and
 * implements check on prod. limit AND queue's state for exiting thread.
 * @param service                       Service routine consuming requests
 * @param barrier                       Barrier semaphore, signaled with thread's exiting
 * @return                              Request popped
 */
Request Buffer::retrieve(RequestTransactionService* service, sem_t* barrier) {
    pthread_mutex_lock(&this->mutex); // START of Critical Section

    // Pull request from queue
    Request req = this->trade_req_queue.front();
    this->trade_req_queue.pop();

    // Update values tracking reqs consumed & reqs in queue
    service->reqs_consumed[req.idx]++;
    this->queue_tracker[req.idx]--;

    // Log removal
    log_request_removed(service->type, req.type,
                            service->reqs_consumed, queue_tracker);

    // Check if prod. limit reached AND queue empty
    if (getProductionSum() >= prod_limit && isEmpty()) { // Signal barrier and exit thread!
        pthread_mutex_unlock(&this->mutex);
        sem_post(barrier);
        pthread_exit(nullptr);
    }

    pthread_mutex_unlock(&this->mutex); // END of Critical Section

    return req;
}

/**
 * isEmpty() checks if queue contains elements
 * @return                              Boolean representing state
 */
bool Buffer::isEmpty() {
    return this->trade_req_queue.empty();
}

/**
 * getProductionSum() returns total reqs produced via adding BTC & ETH requests
 * @return                              Total # of reqs
 */
int Buffer::getProductionSum() {
    return this->reqs_produced[0] + this->reqs_produced[1];
}
