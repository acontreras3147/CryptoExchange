/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Service.cpp implements constructors for the various service routines
 */

#include "Service.h"

TradeRequestService::TradeRequestService(RequestType type) {
    this->type = type;
}

RequestTransactionService::RequestTransactionService(ConsumerType type) {
    this->type = type;
}