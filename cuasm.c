#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <errno.h>
#include "htoi.h"

#define MAXLINE 1024

int main(int argc, char *argv[])
{
    char *name = basename(argv[0]);
    FILE *in_file = stdin;
    if (argc > 1) {
        in_file = fopen(argv[1], "r");
        if (in_file == NULL) {
            perror(argv[1]);
            exit(errno);
        }
    }

    char buf[MAXLINE + 1];
    while (fgets(buf, MAXLINE + 1, in_file) != NULL) {
        printf("%s = %lu\n",buf, htoi(buf));
    }

    if (in_file != stdin) {
        fclose(in_file);
    }

    return 0;
}
