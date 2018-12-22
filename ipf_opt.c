#include "inc/ipf_opt.h"
#include "inc/ip_packet.h"

/** insert the fragment into the linkedlist
 *  represent the fragment table.
 *  treat the 'ipq_next' and the 'ipq_prev'
 *  as head and tail.
 *
 * \pkt the packet is a fragment, MF bit is set.
 * \frag the new comming fragment
 * \return void
 *
 */

void
ipf_insert(packet* apkt, struct ipasfrag* frag)
{
    struct ip_queue_packet *pkt = apkt;

    if (pkt->ipq_next == NULL)
    {
        frag->ipf_next = frag;
        frag->ipf_prev = frag;
        pkt->ipq_next = frag;
        pkt->ipq_prev = frag;

        return;
    }

    // from back to front
    struct ipasfrag *p = pkt->ipq_prev;
    while (p != pkt->ipq_next
        && p->ip_off > frag->ip_off)
    {
#ifdef _IPF_DEBUG
        printf("%d ", p->ip_id);
#endif // IPF_DEBUG
        p = p->ipf_prev;
    }

    if (p == pkt->ipq_prev)
        pkt->ipq_prev = frag;

    frag->ipf_next = p->ipf_next;
    frag->ipf_prev = p;
    frag->ipf_next->ipf_prev = frag;
    p->ipf_next = frag;
#ifdef _IPF_DEBUG
        char * str = "\n[prev MF : %d length : %d offset : %d] ->\n"
                        "[frag MF : %d length : %d offset : %d] ->\n"
                        "[next MF : %d length : %d offset : %d] \n\n";
        printf(str, frag->ipf_prev->ipf_mff, frag->ipf_prev->ip_len, frag->ipf_prev->ip_off,
                    frag->ipf_mff, frag->ip_len, frag->ip_off,
                    frag->ipf_next->ipf_mff, frag->ipf_next->ip_len, frag->ipf_next->ip_off);
#endif // IPF_DEBUG

}

/**
 *  allocate a new ip packet fragment
 */
struct ipasfrag *
ipf_alloc()
{
    struct ipasfrag *p = (struct ipasfrag *) malloc(sizeof(struct ipasfrag));
    memset(p, 0, sizeof(struct ipasfrag));
    return p;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void
ipf_destroy(packet *pkt)
{
    if (pkt->ipq_next == NULL)
        return;
    struct ipasfrag *p, *freeptr;
    p = freeptr = pkt->ipq_next;
    while (p != pkt->ipq_prev) {
        p = p->ipf_next;
        free(freeptr);
        freeptr = p;
    }
    free(p);

    freeptr = p = NULL;
    pkt->ipq_prev = pkt->ipq_next = NULL;

}


/** \brief
 *
 * \pkt is a packet whose table has a MF bit fragment.
 * \param
 * \return
 *
 */
struct packet_info *
ipf_fragment_reorganization(const struct ip_queue_packet* pkt)
{
    struct ipasfrag *p = pkt->ipq_prev;
    int length_sum = 0;
    int data_length = p->ip_off + p->ip_len;
    struct packet_info *info = (struct packet_info *)
                                malloc (sizeof(struct packet_info) + data_length);
    while (p != pkt->ipq_next) {
        memcpy((void *)(info->data.address) + p->ip_off, p->data.address, p->ip_len);
        length_sum += p->ip_len;
        p = pkt->ipq_next;
    }
    memcpy((void *)(info->data.address) + p->ip_off, p->data.address, p->ip_len);
    length_sum += p->ip_len;

    if (data_length != length_sum) {
        // this table is incompleted;
        free (info);
        return NULL;
    }

    info->data.buffsize = data_length;
    info->version = p->ip_v;

    return info;
}


/**
 *  print all fragment
 */
void
ipf_printall(packet *pkt)
{
    if (pkt->ipq_next == NULL)
    {
        for (int i = 0; i < 8; i++)
            printf("-");
        printf("(none)\n");
    }
    //printf("head %d, tail %d", pkt->ipq_next->ip_off, pkt->ipq_prev->ip_off);
    struct ipasfrag *p = pkt->ipq_next;
    while (p != pkt->ipq_prev) {
        ipf_print(p);
        p = p->ipf_next;
    }
}

void
ipf_print(struct ipasfrag * frag)
{
    for (int i = 0; i < 8; i++)
        printf("-");
    char * outstr = "[vesion] %d [head length] %d [MF] %d [fragment length] %d \n"
                    "\t[packet id] %d [offset] %d [TTL] %d [protocal] %d [sum] %d\n";
    printf(outstr, frag->ip_v, frag->ip_hl, frag->ipf_mff, frag->ip_len,
                    frag->ip_id, frag->ip_off, frag->ip_ttl, frag->ip_p, frag->ip_sum);
}


