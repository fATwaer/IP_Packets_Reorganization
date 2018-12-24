#ifndef NETPKT_H_INCLUDED
#define NETPKT_H_INCLUDED
#include "../lib/types.h"
#include <stdlib.h>
#include <string.h>

/** packed: 20 bytes */
struct network_packet {
    uint8_t np_v:4;
    uint8_t np_hl:4;
    uint8_t np_tos;
    uint16_t np_len;
    uint16_t np_id;
    uint8_t np_mf:3;
    uint16_t np_off:13;
    uint8_t np_ttl;
    uint8_t np_p;
    uint16_t np_sum;
    uint32_t np_src;
    uint32_t np_dst;
    char np_data[0];
} __attribute__ ((__packed__)); // must be packed



struct packet_option {
    uint8_t po_code;
    uint8_t po_len;
    char np_data[0];
};

struct network_packet * netpkt_alloc(int mtu, int optlen);
struct network_packet *
netpkt_fill(struct network_packet *pkt, uint32_t src,
                uint32_t dst, uint8_t mf, uint16_t id);
struct network_packet *
netpkt_setoff(struct network_packet *pkt, uint16_t offset);

#endif // NETPKT_H_INCLUDED
