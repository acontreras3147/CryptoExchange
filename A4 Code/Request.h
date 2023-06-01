/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Request.h defines Request's members
 */

#ifndef REQUEST_H
#define REQUEST_H

#include "cryptoexchange.h"

class Request {
public:
    Request(RequestType type);

    RequestType type;
    int idx;
};


#endif //REQUEST_H
