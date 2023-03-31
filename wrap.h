//
// Created by john on 31.03.23.
//

#pragma once
#include <bits/types/FILE.h>

int Printf(char *, ...);
int Fprintf (FILE *, char *, ...);
char *Fgets(char *, int, FILE *);
void Fputs(const char *, FILE *s);
FILE *Popen(const char *, const char *);
void Fclose(FILE *);
void Pclose (FILE *s);
