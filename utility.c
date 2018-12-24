#include "lib/lib.h"

//#include "lib/_color_print.h"

void
err_exit(char * err_msg)
{
    print_red(err_msg);
    fflush(stdout);
    perror(NULL);
    exit(-1);
}

void
print_red(char *str)
{
    RED_PRINT;
    fprintf(stdout, str);
    fflush(stdout);
    NORMAL_PRINT;
}

void
print_green(char *str)
{
    GREEN_PRINT;
    fprintf(stdout, str);
    fflush(stdout);
    NORMAL_PRINT;
}

void
err_print(char * err_msg)
{
    print_red(err_msg);
    fflush(stdout);
}



