#include "inc/ip_queue.h"
#include "pthread.h"
#include <stdlib.h>

ipq *ipq_head;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static ipq* ipq_tail;

void
ipq_init()
{
    ipq_head = NULL;
    ipq_tail = NULL;
}

packet *
ipq_alloc()
{
    return (packet *)malloc(sizeof(packet));
}

int
ipq_push(packet *pkt)
{
    pthread_mutex_lock(&mutex);
    if (ipq_head == NULL)
    {
        ipq_head = pkt;
        ipq_head->next = pkt;
        ipq_head->prev = pkt;
    }

    ipq *p = ipq_head;

    while (p != ipq_head || p->ipq_id < pkt->ipq_id) {
        p = p->next;
    }

    pkt->prev = p->prev;
    pkt->next = p;
    p->prev->next = pkt;
    p->prev = pkt;


    pthread_mutex_unlock(&mutex);

    return 0;
}


packet *
ipq_pop()
{

}

packet *
ipq_search(uint16_t ip_id)
{

}


