#include "assert.h"
#include "inc/ip_queue.h"
#include "inc/ipq_opt.h"
#include "inc/ipf_opt.h"
#include "inc/unit_test.h"
#include "math.h"
#include "lib/_color_print.h"
#include "inc/ip_packet.h"

/** ipq  */
void
ut_ipq_insert_destroy()
{
    ipq_init();

    for (int i = 1; i < 40; i += 2) {
        packet *p = ipq_alloc();
        p->ipq_id = i;
        ipq_push(p);
    }

    packet *p = ipq_alloc();
    p->ipq_id = 22;
    ipq_push(p);

    p = ipq_search(22);
    assert(p->ipq_id == 22);
    printf("IPQ insert assert");
    print_green(" success\n");
    assert(ipq_getTail()->ipq_id == 39);
    queue_print();
    printf("\n");
    ipq_delete(ipq_search(22));
    queue_print();
    ipq_destroy();

}

/** ipf */
void
ut_ipf_insert_destroy()
{

    ipq_init();

    struct ip_queue_packet *p = ipq_alloc();
    p->ipq_id = 22;
    ipq_push(p);

    struct ipasfrag *fragptr;

    for (int i = 0; i <= IPF_MTU * (int)ceil(flr_PKTSZ/IPF_MTU); i += IPF_MTU) {
        fragptr = ipf_alloc(0);

        if (i + IPF_MTU > PKTSZ)
            fragptr->ip_len = PKTSZ - i;
        else {
            fragptr->ip_len = PKTSZ;
            fragptr->ipf_mff |= 1;
        }

        fragptr->ip_id = 22;
        fragptr->ip_off = i;
        ipf_insert(p, fragptr);
    }
    //ipf_printall(p);

    ipq_destroy();

    assert(p->ipq_next == NULL);
    printf("IPF insert assert");
    print_green(" success\n");

}

void
ut_ipf_reorganization()
{
    printf("[unit test] ut_ipf_reorganization ...\n");

    ipq_init();
    struct ip_queue_packet *p = ipq_alloc();
    p->ipq_id = 22;
    ipq_push(p);

    struct ipasfrag *fragptr;
    char data[9];
    int len = PERSZ;
    char ch = 'A';
    for (int i = 0; i < PERSZ * (int)ceil(flr_PKTSZ2/PERSZ); i+= PERSZ) {
        if (i + PERSZ > PKTSZ2) {
            fragptr = ipf_alloc(PKTSZ2 - i);
            fragptr->ip_len = PKTSZ2 - i;
            len = PKTSZ2 - i;
        } else {
            fragptr = ipf_alloc(len);
            fragptr->ip_len = PERSZ;
            fragptr->ipf_mff |= 1;
        }
        memset(data, ch + i, len);
        memcpy(fragptr->data.address, data, len);
        fragptr->data.buffsize = len;
        fragptr->ip_id = 22;
        fragptr->ip_off = i;
        ipf_insert(p, fragptr);
    }
    ipf_printall(p);
    struct packet_info *info = ipq_pop();
    assert(info != NULL);
    assert(info->data.buffsize == PKTSZ2);

    char buff[PKTSZ2+1];
    buff[PKTSZ2] = '\0';
    memcpy(buff, info->data.address, PKTSZ2);
    printf("reorganization data: %s\n", buff);
    printf("reorganization insert assert");
    print_green(" success\n");
    free(info);

    ipq_destroy();
}
