/**
 * Anthony Norderhaug, Anthony Contreras
 * CS 480 - Spring 2023
 * RedID: 823899304, 824089247
 *
 * Brokerage.cpp initializes & modifies the service routines according to optional arguments.
 */

#include "Brokerage.h"

/**
 * createServices() initializes service routines associated with Producer & Consumer threads. Processing times set
 * to 0ms.
 */
void Brokerage::createServices() {
    this->producers = new TradeRequestService[2]{
            TradeRequestService(Bitcoin), TradeRequestService(Ethereum)};
    this->consumers= new RequestTransactionService[2]{
            RequestTransactionService(BlockchainX), RequestTransactionService(BlockchainY)};
}

/**
 * Brokerage constructor, parses optional command-line args to tweak production limit & service routine info.
 * @param argc                          Arg count
 * @param argv                          Args
 */
Brokerage::Brokerage(int argc, char **argv) {
    createServices(); // Initialized w/ defaults

    // Parsing and applying command-line arguments
    int option = 0;
    while ((option = getopt(argc, argv, "r:x:y:b:e:")) != -1) {
        switch (option) {
            // Production Limit
            case 'r': {
                prod_limit = atoi(optarg);
                break;
            }
            // Blockchain X processing rate
            case 'x': {
                this->consumers[BLOCKCHAIN_X_IDX].processing_time = atoi(optarg);
                break;
            }
            // Blockchain Y processing rate
            case 'y': {
                this->consumers[BLOCKCHAIN_Y_IDX].processing_time = atoi(optarg);
                break;
            }
            // Bitcoin production rate
            case 'b': {
                this->producers[BTC_IDX].processing_time = atoi(optarg);
                break;
            }
            // Ethereum production rate
            case 'e': {
                this->producers[ETH_IDX].processing_time = atoi(optarg);
                break;
            }
            case ':': {
                cout << "Option '" << optopt << "' was not given a parameter. Applying default.";
                break;
            }
            case '?': {
                cout << "Unknown argument '" << optopt << "'";
                exit(1);
            }
            default: {
                printf("Usage: ./cryptoexc -r -x -y -b -e");
                exit(1);
            }
        }
    }
}
