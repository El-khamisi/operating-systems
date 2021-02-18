//
// Created by el5amisi on 2/18/21.
//

#ifndef WEBSOCKET_SERVER_HEADER_H
#define WEBSOCKET_SERVER_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>


#define SERVER_PORT 15000
#define MAXLINE 256




//Handling Error
void err_n_die(const char *str, ...);

#endif //WEBSOCKET_SERVER_HEADER_H
