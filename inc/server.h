#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
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

#define SERVBUFMAXLINE 4096
#define SERVBACKLOG 5
#define ROOTDIR "/home/moonlight/IP_Packets_Reorganization/"
#define DEFMTU 500

void server(int port);
void send_file_fragment(char *file_path, int connfd, uint32_t src, uint32_t dst, uint16_t id);

#endif // SERVER_H_INCLUDED
