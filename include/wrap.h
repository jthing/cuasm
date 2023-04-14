//
// Created by john on 31.03.23.
//

#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4096
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

char *skip_word(const char *);
char *skip_ws(const char *);
char *opt_val(char *, char **, char **);
char *get_word(char *, char **);

void *Calloc(size_t, size_t);
void *Malloc(size_t);
void *Realloc(void *, size_t);
void *Memcpy(void *, const void *, size_t);
char *Strdup(const char *);
int Streq(const char*, const char *);
int Fprintf (FILE *, const char *, ...);
int Snprintf(char *str, size_t size, const char *fmt, ...);
size_t Fwrite (const void *, size_t, size_t, FILE *);
size_t Fread (void *, size_t, size_t, FILE *s);
char *Fgets(char *, int, FILE *);
void Fputs(const char *, FILE *s);
FILE *Popen(const char *, const char *);
void Fclose(FILE *);
void Pclose (FILE *s);
void Warning(const char *, ...);
void DEBUG(const char *, ...);
void Error(const char *, ...);

