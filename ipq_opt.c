#include "inc/ipq_opt.h"
#include "pthread.h"
#include "inc/ipf_opt.h"
#include "inc/ip_packet.h"

struct ip_queue_packet *head;
#define ipq_head  (head->next)
#define ipq_tail  (head->prev)
//ipq *ipq_head;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//static ipq* ipq_tail;
static int isInit = false;


void
ipq_init()
{
    head = (struct ip_queue_packet *) malloc (sizeof(struct ip_queue_packet));
    head->next = NULL;
    head->prev = NULL;
    isInit = true;
}

packet *
ipq_alloc()
{
    packet *p = (packet *)malloc(sizeof(packet));
    memset(p, 0, sizeof(packet));
    return p;
}

void
ipq_push(packet *pkt)
{
    if (!isInit)
        perror("ipq is not initialized");

    pthread_mutex_lock(&mutex);

    if (ipq_head == NULL)
    {
        ipq_head = pkt;
        ipq_head->next = pkt;
        ipq_head->prev = pkt;
        ipq_tail = pkt;

        return;
    }

    ipq *p = ipq_head->next;

    while (p != ipq_head
        && p->ipq_id < pkt->ipq_id) {
        p = p->next;
    }

    if (p == ipq_head)
        ipq_tail = pkt;

    pkt->prev = p->prev;
    pkt->next = p;
    p->prev->next = pkt;
    p->prev = pkt;

    pthread_mutex_unlock(&mutex);

}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


struct packet_info *
ipq_pop()
{
    struct packet_info *p;

    // find a packet, MF is 0;
    //
    // TODO


    ipf_fragment_reorganization(ipq_head);


    return NULL;
}


void
ipq_destroy() {
    pthread_mutex_lock(&mutex);
    if (!isInit)
        return;

    struct ip_queue_packet *freeptr, *p;
    freeptr = p = ipq_head;

    while (p != ipq_tail) {
        p = p->next;

        // clean fragment
        ipf_destroy(freeptr);

        free(freeptr);
        freeptr = p;
    }
    free(p);

    p = freeptr = NULL;
    ipq_head = ipq_tail = NULL;

    pthread_mutex_unlock(&mutex);
}

const packet *
ipq_getTail()
{
    return ipq_tail;
}

const packet *
ipq_getHead()
{
    return ipq_head;
}

packet *
ipq_search(uint16_t ip_id)
{
    if (ip_id == ipq_head->ipq_id)
        return ipq_head;

    packet *p = ipq_head->next;

    while (p != ipq_head)
    {
        if (ip_id == p->ipq_id)
            return p;
        p = p->next;
    }
    return NULL;
}



void
queue_print()
{
    packet *p = ipq_head->next;

    printf("id = %d\n", ipq_head->ipq_id);
    while (p != ipq_head) {
        printf("id = %d\n", p->ipq_id);
        p = p->next;
    }

}


