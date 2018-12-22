#ifndef  _IP_QUEUE_H
#define  _IP_QUEUE_H
#include "../lib/types.h"
#include "../lib/lib.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

struct ipasfrag {
    unsigned char ip_v:4;
    unsigned char ip_hl:4;
    uint8_t ipf_mff;        // MF
    uint16_t ip_len;
    uint16_t ip_id;
    uint16_t ip_off;
    uint8_t ip_ttl;
    uint8_t ip_p;
    uint16_t ip_sum;
    struct ipasfrag* ipf_next;
    struct ipasfrag* ipf_prev;
    struct packetdata data;
}__attribute__ ((__packed__));



typedef struct ip_queue_packet {
    struct ip_queue_packet* next;
    struct ip_queue_packet* prev;
    uint16_t ipq_ttl;
    uint16_t ipq_p;                  //  16bit protocol
    uint32_t ipq_id;
    struct ipasfrag* ipq_next;
    struct ipasfrag* ipq_prev;
    uint32_t ipq_src;
    uint32_t ipq_dst;
    struct timeval ipq_lt;          // last time fragment arrived
}__attribute__ ((__packed__)) packet, ipq;


enum {
    false = 0,
    true = 1
};

extern ipq *ipq_head;

#endif // _IP_QUEUE_H


