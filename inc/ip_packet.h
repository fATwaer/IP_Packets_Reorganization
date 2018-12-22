#ifndef IP_PACKET_H_INCLUDED
#define IP_PACKET_H_INCLUDED
#include "../lib/lib.h"

struct packet_info {
    uint32_t src;
    uint32_t dst;
    int ttl;
    int id;
    int protocal;
    int version;
    struct packetdata data;
};

#endif // IP_PACKET_H_INCLUDED
