/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Synch.h defines Synch's members
 */

#ifndef SYNCH_H
#define SYNCH_H

#include <semaphore.h>


class Synch {
public:
    Synch(int capacity, int btc_capacity);

    sem_t available_slots; sem_t unconsumed;
    sem_t available_btc_slots;
    sem_t barrier;
};


#endif //SYNCH_H
