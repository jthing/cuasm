//
// Created by john on 29.03.23.
//
#include <stdio.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>

#define MAXLINE 1024

int main(int argc, char *argv[])
{
    char *name = basename(argv[0]);
    if (argc < 1) {
        fprintf(stderr, "Usage: %s <input-file>\n", name);
        return -1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) {
        perror(basename(argv[1]));
        return errno;
    }

    FILE *out = popen("./cuasm", "w");
    if (out == NULL) {
        perror("cuasm");
        return errno;
    }

    char buf[MAXLINE];
    while (fgets(buf, MAXLINE, infile) != NULL) {
        fputs(buf, out);
    }

    fclose(infile);
    pclose(out);

    return 0;
}
