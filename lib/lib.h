#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include "stdlib.h"
#include <stdio.h>
#include "_color_print.h"
#include <errno.h>

void err_exit(char * err_msg);
void err_print(char * err_msg);

struct packetdata {
    int buffsize;
    char address[0];
};
#endif // LIB_H_INCLUDED
