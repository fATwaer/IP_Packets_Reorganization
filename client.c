#include "inc/client.h"

extern int globalmtu;
static int checkthread = false;
static int initqueue = false;

void
client(char *addr, int port)
{
    int     sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, addr, &servaddr.sin_addr);

    if ((connect(sockfd,
                (struct sockaddr *)&servaddr,
                sizeof(servaddr))) < 0) {
        err_exit("[connection]");
    }

    handle_connection_packet(sockfd);

    struct packet_info *p;
//    while ((p = ipq_pop()) == NULL) {
//        printf("NULL\n");
//    }

    p = ipq_pop();
    if (p == NULL)
        err_exit("null");
    printf("[data] : %s\n", p->data.address);
    pause();
}

int
handle_connection_packet(int fd)
{
    int r;
    pthread_t tid, checktid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if ((r = pthread_create(&tid, NULL, handle_packet_routine, (void *)&fd)) != 0)
        err_print("[create thread] error");
    if (!checkthread) {
        if ((r = pthread_create(&checktid, &attr, check_thread_routine, NULL)) != 0)
            err_print("[create thread] error");
        checkthread = true;
    }
    pthread_attr_destroy(&attr);
    pthread_join(tid, NULL);
    return 0;
}

void *
handle_packet_routine(void *args)
{
    int fd = *(int *)args;
    int n, datalen;
    struct network_packet *pkt = netpkt_alloc(20, 0);

    while ((n = readn(fd, pkt, 20)) > 0) {
        printf("offset %d len %d\n", pkt->np_off, pkt->np_len);
        datalen = pkt->np_len - pkt->np_hl * 4;

        struct ipasfrag *frag = ipf_alloc(datalen);
        frag->ip_hl = pkt->np_hl;
        frag->ip_v = pkt->np_v;
        frag->ipf_mff = pkt->np_mf;
        frag->ip_len = pkt->np_len;
        frag->ip_id = pkt->np_id;
        frag->ip_p = pkt->np_p;
        frag->ip_off = pkt->np_off;
        frag->ip_ttl = pkt->np_ttl;
        frag->ip_sum = pkt->np_sum;

        if (readn(fd, frag->data.address, datalen) < 0)
            err_print("[recv error]");

        cli_insert_fragment(frag, pkt->np_src, pkt->np_dst);
    }

    return (void *)0;
}

void
cli_insert_fragment(struct ipasfrag *frag, uint32_t src, uint32_t dst)
{
    struct ip_queue_packet *ipq = NULL;

    if (!initqueue) {
        ipq_init();
        initqueue = true;
    }

    ipq = ipq_search(frag->ip_id);

    if (ipq == NULL) {
        ipq = ipq_alloc();
        ipq->ipq_dst = dst;
        ipq->ipq_src = src;
        ipq->ipq_ttl = frag->ip_ttl;
        ipq->ipq_p = frag->ip_p;
        ipq->ipq_id = frag->ip_id;
        ipq_push(ipq);
    }

    ipf_insert(ipq, frag);
    ipf_printall(ipq);

}


void *
check_thread_routine(void *args)
{
    return NULL;
}


ssize_t
readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        } else if (nread == 0)
            break;

        nleft -= nread;
        ptr += nread;

    }
    return (n - nleft);
}
