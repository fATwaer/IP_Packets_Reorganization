#include "inc/server.h"


extern int hasConfigFile;
extern int hasPacketOpt;
extern int globalmtu;

void
server(int port)
{
    int listenfd, connfd, textfd, logfd, n, i;
    size_t datalen = 0, optlen = 0;
    pid_t pid;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    time_t ticks;
    char buff[SERVBUFMAXLINE] = {0};
    char namebuff[SERVBUFMAXLINE] = {0};

    chdir(ROOTDIR);
    if ((textfd = open("./text/server.file", O_RDONLY)) < 0)
        err_exit("[open text file]");

    if ((logfd = open("./log/server.log", O_RDWR | O_CREAT | O_APPEND, 0644)) < 0)
        err_exit("[open log file]");


    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_exit("[socket]");
    memset(&servaddr, 0, sizeof(servaddr));

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        err_exit("setsockopt(SO_REUSEADDR) failed");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0)
        err_exit("[bind]");

    if ((listen(listenfd, SERVBACKLOG)) < 0)
        err_exit("[listen]");

    for (; ;) {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
        ticks = time(NULL);
        sprintf(buff, "connection from %s, port %d, %.24s\n",
                    inet_ntop(AF_INET, &cliaddr.sin_addr, namebuff, sizeof(namebuff)),
                    ntohs(cliaddr.sin_port),
                    ctime(&ticks));
        write(logfd, buff, sizeof(buff));

        if ((pid = fork()) == 0) {
            close(listenfd);
            close(logfd);

            struct network_packet *pkt = NULL;
            // fill packet
            if (!hasConfigFile) {
                pkt = netpkt_alloc(globalmtu, optlen);
            }

            netpkt_fill(pkt, 0, *((uint32_t *)&cliaddr.sin_addr), 1, 233);
            datalen = globalmtu - pkt->np_hl * 4;
            for (i = 0; (n = read(textfd, buff, datalen)) > 0 && n == datalen; i += datalen) {
                printf("i %d\n", i);
                pkt->np_off = i;
                memcpy((void *)pkt->np_data + optlen, buff, datalen);
                memset(buff, 0, SERVBUFMAXLINE);
                write(connfd, pkt, pkt->np_len);
            }


            printf("i %d n %d \n", i, n);
            // last fragment
            free(pkt);
            pkt = netpkt_alloc(n + 20, optlen);
            netpkt_setoff(pkt, i);
            netpkt_fill(pkt, 0, *((uint32_t *)&cliaddr.sin_addr), 0, 233);
            memcpy((void *)pkt->np_data + optlen, buff, n);
            memset(buff, 0, SERVBUFMAXLINE);
            write(connfd, pkt, pkt->np_len);

            free(pkt);
            lseek(textfd, 0, SEEK_SET);
            close(connfd);
            exit(0);
        }

        close(connfd);
        //clean child process
    }
    exit(0);
}
