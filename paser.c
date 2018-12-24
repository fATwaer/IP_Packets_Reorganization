#include "inc/paser.h"

//int hasConfigFile;
int hasPacketOpt;
int globalmtu;


static struct option long_options[] = {
    {"server",  optional_argument, 0,  's' },
    {"client",  required_argument,       0,  'c' },
    {"port",    required_argument, 0,  0 },
    {"help",  no_argument, 0,  'h' },
    {"file", required_argument,       0,  'f' },
    {"test",  no_argument, 0, 't'},
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

    if (argc < 2)
        print_help();

    while (1) {
        c = getopt_long(argc, argv, "s::c:hf:p:t",
                        long_options, &index);

        if (c == -1)
            break;

        switch (c) {
        case 's':
            printf("server\n");
            if (optarg)
                server(atoi(optarg));
            else
                server(6777);               // never return
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
        case 'f':
            printf("file: %s\n" , optarg);
            memset(key, 0, KEYMAX);
            memset(value, 0, VALUEMAX);
            FILE *fp = fopen(optarg, "r");
            while (fscanf(fp, "%s = %s", key, value) != EOF)
                printf("key %s: value %s\n", key, value);
            fclose(fp);
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
        client(servaddr, servport);         // never return
    else
        print_help();
    return 0;
}

void
print_help()
{
    print_red("[usage error]\n");
    exit(-1);
}
