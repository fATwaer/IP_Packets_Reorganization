#include "inc/netpkt.h"
#include "stdio.h"
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
struct network_packet *
netpkt_alloc(int mtu, int optlen)
{
    struct network_packet *p = (struct network_packet *) malloc(mtu);
    memset(p, 0, mtu);

    p->np_hl = (20 + optlen)/4;
    p->np_len = mtu;
    return p;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
struct network_packet *
netpkt_fill(struct network_packet *pkt, uint32_t src,
            uint32_t dst, uint8_t mf, uint16_t id)
{
    pkt->np_v = 4;
    pkt->np_tos = 0;
    pkt->np_id = id;
    pkt->np_ttl = 0;
    pkt->np_p = 0;
    pkt->np_sum = 0;
    pkt->np_dst = dst;
    pkt->np_src = src;
    pkt->np_mf = mf;

    return pkt;
}


struct network_packet *
netpkt_setoff(struct network_packet *pkt, uint16_t offset)
{
    pkt->np_off = offset;
    return pkt;
}


