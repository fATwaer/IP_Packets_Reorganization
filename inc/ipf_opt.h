#ifndef IPF_OPT_H_INCLUDED
#define IPF_OPT_H_INCLUDED
#include "ip_queue.h"
void ipf_insert(packet* apkt, struct ipasfrag* frag);
struct ipasfrag * ipf_alloc();
void ipf_printall(packet *pkt);
void ipf_print(struct ipasfrag * frag);
void ipf_destroy(packet *pkt);
struct packet_info * ipf_fragment_reorganization(const struct ip_queue_packet* pkt);
#ifdef DEBUG
#define _IPF_DEBUG 0
#endif // DEBUG
#endif // IPF_OPT_H_INCLUDED
