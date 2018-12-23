#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/lib.h"
#include <time.h>
#include <arpa/inet.h>

void client(char *addr, int port);

#endif // CLIENT_H_INCLUDED
