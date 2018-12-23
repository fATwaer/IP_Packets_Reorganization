#include "inc/server.h"


extern int hasConfigFile;

void
server(int port)
{
    int listenfd, connfd, textfd, logfd;
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
        sprintf(buff, "connection from %s, port %d, time %.24s\n",
                    inet_ntop(AF_INET, &cliaddr.sin_addr, namebuff, sizeof(namebuff)),
                    ntohs(cliaddr.sin_port),
                    ctime(&ticks));
        write(logfd, buff, sizeof(buff));

        if ((pid = fork()) == 0) {
            close(listenfd);
            close(logfd);
            //
            //
            //
            //
            close(connfd);
            exit(0);
        }

        close(connfd);
        //clean child process
    }
    exit(0);
}
