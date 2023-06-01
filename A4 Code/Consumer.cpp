/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Consumer.cpp implements the Consumer thread logic and defines the arg ptr ConsumerData
 */

#include "Consumer.h"
#include "log.h"
#include <unistd.h>

/**
 * ConsumerData constructor, storing service routine and ptrs to Buffer & Synch objs
 * @param service                           Service routine
 * @param buffer                            Ptr to associated buffer
 * @param synch                             Ptr to associated synch obj
 */
ConsumerData::ConsumerData(RequestTransactionService service, Buffer* buffer, Synch* synch) : service(service) {
    this->buffer = buffer;
    this->synch = synch;
}

/**
 * consume() completes trade requests from the queue, utilizing semaphores to synchronize with producers in identifying
 * unconsumed requests and signaling available slots. Sleeps to simulate request consumption. Capable of exiting during
 * buffer access.
 * @param arg                               Ptr holding ConsumerData fields
 */
void* consume(void* arg) {
    auto* cd = (ConsumerData*) arg; // Arguments ptr

    while (true) {
        // 1. Wait for request to be added onto queue
        sem_wait(&cd->synch->unconsumed);

        // 2. Pull request off of queue
        // 'retrieve()' contains Production Limit & queue check, capable of ending thread!
        Request req = cd->buffer->retrieve(&cd->service, &cd->synch->barrier);

        // 3. Signal that space has been freed up
        if (req.type == Bitcoin) { // Bitcoin req, signal BTC semaphore
            sem_post(&cd->synch->available_btc_slots);
        }
        sem_post(&cd->synch->available_slots); // Signal general availability semaphore

        // 4. Simulate consumption via sleeping
        usleep(cd->service.processing_time * MILLI_TO_MICRO);
    }
}
