/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Brokerage.h defines its members and several constants related to Assignment #4's constraints
 */

#ifndef ARGS_H
#define ARGS_H

#include "cryptoexchange.h"
#include "Service.h"
#include "getopt.h"
#include <iostream>

#define DEFAULT_PRODUCTION_LIMIT 100

// System constraints.
#define BUFFER_CAPACITY 16
#define BITCOIN_CAPACITY 5

// For readability.
#define BTC_IDX 0
#define ETH_IDX 1
#define BLOCKCHAIN_X_IDX 0
#define BLOCKCHAIN_Y_IDX 1

using namespace std;

class Brokerage {
public:
    Brokerage(int argc, char** argv);

    int prod_limit = DEFAULT_PRODUCTION_LIMIT;
    int queue_limit = BUFFER_CAPACITY;
    int btc_limit = BITCOIN_CAPACITY;

    TradeRequestService* producers;
    RequestTransactionService* consumers;

    void createServices();
};


#endif //ARGS_H
