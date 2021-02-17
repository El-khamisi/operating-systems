

#ifndef WEBSOCKET_CLIENT_HEADER_H
#define WEBSOCKET_CLIENT_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>


#define SERVER_PORT 9002
#define MAXLINE 256




//Handling Error
void err_n_die(const char *str, ...);

#endif //WEBSOCKET_CLIENT_HEADER_H
