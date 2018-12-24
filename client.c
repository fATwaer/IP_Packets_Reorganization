#include "inc/client.h"

extern int globalmtu;

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

    pause();
}

int
handle_connection_packet(int fd)
{
    int r;
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if ((r = pthread_create(&tid, &attr, handle_packet_routine, (void *)&fd)) != 0)
        err_print("[create thread] error");

    return 0;
}

void *
handle_packet_routine(void *args)
{
    int fd = *(int *)args;
    int n, datalen;
    struct network_packet *pkt = netpkt_alloc(globalmtu, 0);

    while ((n = readn(fd, pkt, 20)) > 0) {
        printf("offset %d len %d\n", pkt->np_off, pkt->np_len);
        datalen = pkt->np_len - pkt->np_hl * 4;
        if (read(fd, pkt->np_data, datalen) < 0)
            err_print("[recv error]");

    }

    return (void *)0;
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
