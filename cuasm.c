#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include "htoi.h"

#define MAXLINE 1024

char *Fgets(char *s, int size, FILE *stream)
{
    char *ret = fgets(s, size, stream);
    if (ret == NULL && ferror(stream)) {
        perror("fgets: ");
        exit(errno);
    }
    return ret;
}

int Printf(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    int ret = vprintf(fmt, ap);
    if (ret < 0) {
        perror("printf: ");
        exit(errno);
    }
    return ret;
}

void Fclose(FILE *file)
{
    int ret = fclose(file);
    if (ret == EOF) {
        perror("fclose: ");
        exit(errno);
    }
}

int main(int argc, char *argv[])
{
    FILE *in_file = stdin;
    if (argc > 1) {
        in_file = fopen(argv[1], "r");
        if (in_file == NULL) {
            perror(argv[1]);
            exit(errno);
        }
    }

    char buf[MAXLINE + 1];
    while (Fgets(buf, MAXLINE + 1, in_file) != NULL) {
        Printf("%s = %lu\n",buf, htoi(buf));
    }

    if (in_file != stdin) {
        Fclose(in_file);
    }

    return 0;
}

