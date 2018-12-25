#include "inc/paser.h"

//int hasConfigFile;
int hasPacketOpt;
int globalmtu;
unsigned int packeDelay;
size_t optlen;

static struct option long_options[] = {
    {"server",  optional_argument, 0,  's' },
    {"client",  required_argument,       0,  'c' },
    {"port",    required_argument, 0,  0 },
    {"help",  no_argument, 0,  'h' },
    {"file", required_argument,       0,  'f' },
    {"test",  no_argument, 0, 't'},
    {"dalay", required_argument, 0, 'd'},
    {0,         0,         0,  0 }
};

int
paser_commandline(int argc, char *argv[])
{
    int c;
    int index = 0;
    // for client to connect server
    int servport = 0;
    char servaddr[ADDRMAXLEN], key[KEYMAX], value[VALUEMAX];

    globalmtu = 500;
    packeDelay = 0;
    optlen = 0;

    if (argc < 2)
        print_help();

    while (1) {
        c = getopt_long(argc, argv, "d:s::c:hf:p:t",
                        long_options, &index);

        if (c == -1)
            break;

        switch (c) {
        case 's':
            print_red("[server] ");
            printf("start\n");
            if (optarg)
                server(atoi(optarg));
            else
                server(6777);               // never return
            break;
        case 'h':
            print_help();
            break;
        case 'c':
            print_red("[client] ");
            printf(" connect to %s\n", optarg);
            strncpy(servaddr, optarg, strlen(optarg));
            break;
        case 'p':
            servport = atoi(optarg);
            break;
        case 'f':
            printf("file: %s\n" , optarg);
            memset(key, 0, KEYMAX);
            memset(value, 0, VALUEMAX);
            FILE *fp = fopen(optarg, "r");
            while (fscanf(fp, "%s = %s", key, value) != EOF)
                printf("key %s: value %s\n", key, value);
            //
            //
            fclose(fp);
            break;
        case 'd':
            packeDelay = atoi(optarg);
            break;
        case 't':
            ut_ipf_insert_destroy();
            ut_ipq_insert_destroy();
            ut_ipf_reorganization();
            exit(0);
            break;
        default:
            ;
        }
    }
    if (servport != 0 && servaddr != NULL)
        client(servaddr, servport);         // never return
    else
        print_help();
    return 0;
}


 static struct help_info help[] = {
    {"-c", "start client"},
    {"-s", "start server"},
    {"-d", "set delay"},
    {"-t", "unit test"},
    {"-p", "server port the client connect to"},
    {"-h", "help infomation"},
    {"-f", "set config file"},
    {0, 0}
};

void
print_help()
{
    print_red("[usage error]\n");
    for (int i = 0; help[i].key != NULL || help[i].value != NULL; i++) {
        printf("%s\t%s\n", help[i].key, help[i].value);
    }
    exit(-1);
}
