//
// Created by john on 31.03.23.
//

#pragma once
#include <bits/types/FILE.h>

int Printf(const char *, ...);
int Fprintf (FILE *, const char *, ...);
int Snprintf(char *str, size_t size, const char *fmt, ...);
char *Fgets(char *, int, FILE *);
void Fputs(const char *, FILE *s);
FILE *Popen(const char *, const char *);
void Fclose(FILE *);
void Pclose (FILE *s);

