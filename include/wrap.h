//
// Created by john on 31.03.23.
//

#pragma once

#include <bits/types/FILE.h>

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
typedef enum {false, true} bool;

void *Calloc(size_t, size_t);
void *Malloc(size_t);
void *Realloc(void *, size_t);
void *Memcpy(void *, const void *, size_t);
char *Strdup(const char *);
int Streq(const char*, const char *);
int Fprintf (FILE *, const char *, ...);
int Snprintf(char *str, size_t size, const char *fmt, ...);
char *Fgets(char *, int, FILE *);
void Fputs(const char *, FILE *s);
FILE *Popen(const char *, const char *);
void Fclose(FILE *);
void Pclose (FILE *s);
void Warning(const char *, ...);
void DEBUG(const char *, ...);
void Error(const char *, ...);

