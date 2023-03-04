

#ifndef MULTITHREADINGRW_HEADER_H
#define MULTITHREADINGRW_HEADER_H

#include <iostream>
#include <unistd.h>
#include <pthread.h>



/*
 * Main Thread function for Reading purpose
 * Execute multi Reader whenever there is no Writer in use
 */
void *mainReader(void *arg);

/*
 * Main Thread function for Writing purpose
 * Execute ONE Writer whenever theres is no Reader in use
 * And only ONE Writer can execute
 */
void *mainWriter(void *arg);


#endif //MULTITHREADINGRW_HEADER_H
