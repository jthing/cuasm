#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "htoi.h"
#include "wrap.h"

#define MAXLINE 1024

int main (int argc, char *argv[])
{
  FILE *in_file = stdin;
  if (argc > 1)
	{
	  in_file = fopen (argv[1], "r");
	  if (in_file == NULL)
		{
		  perror (argv[1]);
		  exit (errno);
		}
	}

  char buf[MAXLINE + 1];
  while (Fgets (buf, MAXLINE + 1, in_file) != NULL)
	{
	  Printf ("%s = %lu\n", buf, htoi (buf));
	}

  if (in_file != stdin)
	{
	  Fclose (in_file);
	}

  return 0;
}

