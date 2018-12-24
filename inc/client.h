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
#include <pthread.h>
#include "ipq_opt.h"
#include "ipf_opt.h"
#include "ip_packet.h"
#define CLIBUFMAXLINE 4096

void client(char *addr, int port);
ssize_t readn(int fd, void *vptr, size_t n);
int handle_connection_packet(int fd);
void * handle_packet_routine(void *args);
void cli_insert_fragment(struct ipasfrag *frag, uint32_t src, uint32_t dst);
void * check_thread_routine(void *args);
#endif // CLIENT_H_INCLUDED
