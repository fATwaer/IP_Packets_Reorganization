#include "inc/server.h"


extern int hasConfigFile;
extern int hasPacketOpt;
extern int globalmtu;
extern unsigned int packeDelay;
extern size_t optlen;
extern char textdir[];

void
server(int port)
{
    int listenfd, connfd, logfd;
    pid_t pid;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    time_t ticks;
    DIR *dirptr;
    struct dirent *entry;
    char namebuff[SERVBUFMAXLINE] = {0};
    char buff[SERVBUFMAXLINE] = {0};

    if ((logfd = open("./log/server.log", O_RDWR | O_CREAT | O_APPEND, 0644)) < 0)
        err_exit("[open log file]");

    if ((dirptr = opendir(textdir)) == NULL)
        err_exit("[open dir error]");

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

    signal(SIGCHLD, SIG_IGN);

    for (; ;) {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
        ticks = time(NULL);
        sprintf(buff, "connection from %s, port %d, %.24s\n",
                    inet_ntop(AF_INET, &cliaddr.sin_addr, namebuff, sizeof(namebuff)),
                    ntohs(cliaddr.sin_port),
                    ctime(&ticks));
        print_green("[new conncetion]\n");
        printf("%s\n", buff);
        write(logfd, buff, sizeof(buff));

        int id;
        srand(time(NULL));
        seekdir(dirptr, 0);

        while ((entry = readdir(dirptr))!= NULL) {
            if (!(entry->d_type & DT_DIR))
            {
                printf("transfer %s\n", entry->d_name );
                id = rand()%65536;

                if ((pid = fork()) == 0) {
                    close(listenfd);
                    close(logfd);

                    // generate a packet id

                    chdir(textdir);
                    send_file_fragment(entry->d_name, connfd, 0, *((uint32_t *)&cliaddr.sin_addr), id);

                    close(connfd);
                    exit(0);
                }
            }

        }

        close(connfd);
        //clean child process
        // todo
    }
    exit(0);
}

void
send_file_fragment(char *file_path, int connfd, uint32_t src, uint32_t dst, uint16_t id)
{
    int textfd, datalen = 0;
    int i, n;
    char buff[SERVBUFMAXLINE] = {0};

    if ((textfd = open(file_path, O_RDONLY)) < 0)
        err_exit("[open text file]");

    struct network_packet *pkt = NULL;
            // fill packet

    pkt = netpkt_alloc(globalmtu, optlen);


    netpkt_fill(pkt, 0, dst, 4, id);
    datalen = globalmtu - pkt->np_hl * 4;
    for (i = 0; (n = read(textfd, buff, datalen)) > 0 && n == datalen; i += datalen) {
        printf("[id] %5d [offset] %4d [len] %3d\n", id, i, datalen);
        //pkt->np_off = i;
        netpkt_setoff(pkt, i);
        memcpy((void *)pkt->np_data + optlen, buff, datalen);
        memset(buff, 0, SERVBUFMAXLINE);
        sleep(packeDelay);
        write(connfd, pkt, pkt->np_len);
    }
    sleep(packeDelay);
    printf("[id] %5d [offset] %4d [len] %3d ", id, i, n);
    print_red("#[last fragment]");
    printf("\n");
    fflush(stdout);
    // last fragment
    free(pkt);
    pkt = netpkt_alloc(n + 20, optlen);
    netpkt_fill(pkt, 0, dst, 0, id);
    netpkt_setoff(pkt, i);
    //pkt->np_off = i;
    memcpy((void *)pkt->np_data + optlen, buff, n);
    memset(buff, 0, SERVBUFMAXLINE);
    write(connfd, pkt, pkt->np_len);

    free(pkt);
    close(textfd);
}

