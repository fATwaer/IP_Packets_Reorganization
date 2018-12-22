#ifndef IPQ_OPT_H_INCLUDED
#define IPQ_OPT_H_INCLUDED
#include "ip_queue.h"

void ipq_init();
packet * ipq_alloc();
const packet * ipq_getHead();
const packet * ipq_getTail();
void ipq_push(packet *pkt);
packet * ipq_search(uint16_t ip_id);
void queue_print();
void ipq_destroy();
struct packet_info * ipq_pop();

#endif // IPQ_OPT_H_INCLUDED
