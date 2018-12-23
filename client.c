#include "inc/client.h"

void
client(char *addr, int port)
{
    int     sockfd, connfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, addr, &servaddr.sin_addr);

    if ((connfd = connect(sockfd,
                (struct sockaddr *)&servaddr,
                sizeof(servaddr))) < 0) {
        err_exit("[connection]");
    }

    pause();
}
