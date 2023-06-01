/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Request.cpp stores request info and index to facilitate tracking
 */

#include "Request.h"

Request::Request(RequestType type) {
    this->type = type;
    this->idx = type == Bitcoin ? 0 : 1; // Converting RequestType into int
}
