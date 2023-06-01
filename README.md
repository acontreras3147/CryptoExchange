# CryptoExchange
Simulate a cryptoexchange brokerage that employs a producer-consumer communication scheme. Parties will vary amongst each other by their processing rate and allowed amount on the buffer. These attributes will affect the order of request execution, all are then logged with the provided output methods and compared with specific testcases to ensure proper semaphore, thead, and mutex implementation.

# Process
1. Grab command-line args
  * EX: Production limit, processing times
2. Start 2 producer threads and 2 consumer threads
  * ORDER: Bitcoin (p), Ethereum (p), Blockchain X (c), Blockchain Y (c)

![image](https://github.com/acontreras3147/CryptoExchange/assets/104539405/d95cd945-28d1-4dcc-94b8-72dbc4931deb)

3. Threads will place onto & pull from requests via a buffer
 * FIFO, so most likely queue
 * To ensure synchonrization, utilize a mutex to ensure only 1 party is accessing at a time
 * All parties will vary amongst each other via processing time & limited presence parameters

4. End conditions...
 * Producers run until production limit reached
 * Consumers run until production limit reached AND buffer is empty

5. Everyime the buffer is modified, the buffer's state & modifying thread should be outputted via the provided log.c, log.h files
  * Compared w/ GradeScope's request execution order to ensure proper IPC implementation
  
6. Returning to the main thread...
  * Consumer threads will wait for the queue to fill before completing requests
    * With 2 seperate consumers, the production limit being reached will result in 1 perpetually waiting for a "request that's       not coming" and be blocked
  * In this case, the main thread will implement a barrier via a semaphore
    * Consumer threads will have access to this barrier and "unlock it" upon its end condition being reached (stated earlier)
    	* Upon so, main will continue executing
      	* Due to being a parent thread, main is capable of ending its children thread directly or having the OS end them itself           upon completion

# Tasks
 - [ ] Getopt parsing for command-line args

 - [ ] Producer implementation w/ parameters for varying party attributes

 - [ ] Consumer implementation w/ parameters for varying party attributes

 - [ ] Buffer implementation, utilziing mutex and provided output methods

 - [ ] Semaphores for buffer's empty spaces and current requests

 - [ ] Bitcoin semaphore

 - [ ] Barrier implementation within main

 - [ ] Main thread progression, properly initializing threads
