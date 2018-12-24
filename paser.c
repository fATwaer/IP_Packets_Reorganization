#include "inc/paser.h"

int hasConfigFile;
int hasPacketOpt;
int globalmtu;

static struct option long_options[] = {
    {"server",  optional_argument, 0,  's' },
    {"client",  required_argument,       0,  'c' },
    {"port",    required_argument, 0,  0 },
    {"help",  no_argument, 0,  'h' },
    {"file", required_argument,       0,  'f' },
    {"test",  no_argument, 0, 't'},
    {0,         0,                 0,  0 }
};

int
paser_commandline(int argc, char *argv[])
{
    int c;
    int index = 0;
    // for client to connect server
    int servport = 0;
    char servaddr[ADDRMAXLEN];

    globalmtu = 500;

    if (argc < 2)
        print_help();

    while (1) {
        c = getopt_long(argc, argv, "s::c:hf:p:",
                        long_options, &index);

        if (c == -1)
            break;

        switch (c) {
        case 's':
            printf("server\n");
            if (optarg)
                server(atoi(optarg));
            else
                server(6777);
            break;
        case 'h':
            print_help();
            break;
        case 'c':
            printf("client : %s\n", optarg);
            strncpy(servaddr, optarg, strlen(optarg));
            break;
        case 'p':
            servport = atoi(optarg);
            break;
        case 't':
            ut_ipf_insert_destroy();
            ut_ipq_insert_destroy();
            ut_ipf_reorganization();
            break;
        default:
            ;
        }
    }
    if (servport != 0 && servaddr != NULL)
        client(servaddr, servport);
    else
        print_help();
    return 0;
}

void
print_help()
{
    printf("help infomation\n");
}
