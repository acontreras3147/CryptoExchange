/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Synch.cpp implements constructor initializing semaphores according to queue capacities
 */

#include "Synch.h"

Synch::Synch(int capacity, int btc_capacity) {
    // No resources present, so all capacities set to max and all resource indicators set to 0
    sem_init(&this->available_slots, 0, capacity);
    sem_init(&this->unconsumed, 0, 0);
    sem_init(&this->available_btc_slots, 0, btc_capacity);

    // Barrier for ensuring req. consumption finishes before main
    sem_init(&this->barrier, 0, 0);
}
