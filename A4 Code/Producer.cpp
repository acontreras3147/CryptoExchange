/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Producer.cpp implements the Producer thread logic and defines the arg ptr ProducerData
 */

#include "Producer.h"
#include <unistd.h>

/**
 * ProducerData constructor, storing service routine and ptrs to Buffer & Synch objs
 * @param service                           Service routine
 * @param buffer                            Ptr to associated buffer
 * @param synch                             Ptr to associated synch obj
 */
ProducerData::ProducerData(TradeRequestService service, Buffer* buffer, Synch* synch) : service(service) {
    this->buffer = buffer;
    this->synch = synch;
}

/**
 * produce() adds trade requests onto the queue, utilizing semaphores to synchronize with consumers in identifying
 * available slots and signaling unconsumed resources. Sleeps to simulate request production. Capable of exiting during
 * buffer access.
 * @param arg                               Ptr holding ProducerData fields
 */
void* produce(void* arg) {
    auto* pd = (ProducerData*) arg; // Arguments ptr

    while (true) {
        // 1. Simulate production via sleeping
        usleep(pd->service.processing_time * MILLI_TO_MICRO);

        // 2. Wait for available space
        if (pd->service.type == Bitcoin) { // If bitcoin, wait for BTC slots
            sem_wait(&pd->synch->available_btc_slots);
        }
        sem_wait(&pd->synch->available_slots); // General slot availability

        // 3. Add onto queue
        // 'publish()' contains Production Limit check, capable of ending thread!
        pd->buffer->publish(&pd->service, Request(pd->service.type));

        // 4. Signal that request has been added
        sem_post(&pd->synch->unconsumed);
    }
}
