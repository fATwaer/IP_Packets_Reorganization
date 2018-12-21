#include "assert.h"
#include "inc/ip_queue.h"
#include "inc/ipq_opt.h"
#include "inc/ipf_opt.h"
#include "inc/unit_test.h"
#include "math.h"
#include "lib/_color_print.h"

/** ipq  */
void
ipq_unit_test()
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
    printf("iqp insert assert");
    print_green(" success\n");
    assert(ipq_getTail()->ipq_id == 39);
    //queue_print();
    ipq_destroy();

}

/** ipf */
void
ipf_insert_test()
{

    ipq_init();

    struct ip_queue_packet *p = ipq_alloc();
    p->ipq_id = 22;
    ipq_push(p);

    struct ipasfrag *fragptr;

    for (int i = 0; i <= IPF_MTU * (int)ceil(flr_PKTSZ/IPF_MTU); i += IPF_MTU) {
        fragptr = ipf_alloc();

        if (i + IPF_MTU > PKTSZ)
            fragptr->ip_len = PKTSZ - i;
        else {
            fragptr->ip_len = 480;
            fragptr->ipf_mff |= 1;
        }

        fragptr->ip_id = 22;
        fragptr->ip_off = i;
        ipf_insert(p, fragptr);
    }
    ipf_printall(p);

}

