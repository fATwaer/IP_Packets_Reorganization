#ifndef PASER_H_INCLUDED
#define PASER_H_INCLUDED
#include <stdio.h>
#include "stdlib.h"
#include "getopt.h"
#include "server.h"
#include "unit_test.h"
#include "client.h"

#define ADDRMAXLEN 50

int paser_commandline(int argc, char *argv[]);
void print_help();


#endif // PASER_H_INCLUDED