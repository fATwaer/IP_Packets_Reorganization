#include "inc/client.h"

extern int globalmtu;

void
client(char *addr, int port)
{
    int    n, sockfd;
    struct sockaddr_in servaddr;
    char buff[CLIBUFMAXLINE] = {0};


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

    struct network_packet *pkt = netpkt_alloc(globalmtu, 0);
    printf("head len %d\n", globalmtu);
    while ((n = readn(sockfd, pkt, globalmtu)) > 0)  {
        printf("recv offset %d\n", pkt->np_off);
    }

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
