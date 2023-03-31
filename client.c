//
// Created by john on 29.03.23.
//
#include <stdio.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include "wrap.h"

#define MAXLINE 1024

int main (int argc, char *argv[])
{
  char *name = basename (argv[0]);
  if (argc < 1)
	{
	  Fprintf (stderr, "Usage: %s <input-file>\n", name);
	  return -1;
	}

  FILE *infile = fopen (argv[1], "r");
  if (infile == NULL)
	{
	  perror (basename (argv[1]));
	  return errno;
	}

  FILE *out = Popen ("./cuasm", "w");
  if (out == NULL)
	{
	  perror ("cuasm");
	  return errno;
	}

  char buf[MAXLINE];
  while (Fgets (buf, MAXLINE, infile) != NULL)
	{
	  Fputs (buf, out);
	}

  Fclose (infile);
  Pclose (out);

  return 0;
}
