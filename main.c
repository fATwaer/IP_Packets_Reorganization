#include <stdio.h>
#include <stdlib.h>
#include "inc/unit_test.h"


struct packetdata {
    int buffsize;
    char data[0];
};

struct a {
    int abc;
    struct packetdata b;
};

int main()
{
    ut_ipf_insert_destroy();
    ut_ipq_insert_destroy();

    char a[10] = "abcdefg";
    struct a *p = (struct a *) malloc (sizeof(struct a) + 10);
    memcpy(p->b.data, a, sizeof(a));
    printf("data %s", p->b.data);
}
