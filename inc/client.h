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
#include "netpkt.h"
#include <errno.h>

#define CLIBUFMAXLINE 4096
void client(char *addr, int port);
ssize_t
readn(int fd, void *vptr, size_t n);


#endif // CLIENT_H_INCLUDED
