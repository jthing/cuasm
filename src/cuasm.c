/* cuda assembler

Copyright (C) 2023 Pandora Norge

cuasm is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

cuasm is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with cuasm.  If not, see <https://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
#include "wrap.h"

#define MAXLINE 1024
#define MAXCMD 4096

int main (int argc, char *argv[])
{
  int c;
  while ( (c = getopt (argc, argv, "o:")) != -1)
	switch (c)
  		{
	  	case 'o':
			break;
	  	case '?':
			if (optopt == 'o')
		  		Fprintf (stderr, "Option `-%c' requires an argument.\n", optopt);
			else if (isprint (optopt))
		  		Fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
		  		Fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			return 1;
	  	default:
			abort();
		}

  FILE *infile = NULL;
  if(!isatty(STDIN_FILENO))
	{
	  infile = stdin;
	}
  if (optind < argc)
	{
	  infile = fopen (argv[optind], "r");
	  if (infile == NULL)
		{
		  perror (argv[optind]);
		  exit (errno);
		}
	}
  if (infile == NULL)
	{
	  Fprintf(stderr, "Usage: cuasm [-o <outfile>] <infile>\n");
	  exit (1);
	}

  // Pipe the input file through CPP (CPP_PATH) before cuasm_bg (CUASM_PATH)

  char *cpp = getenv ("CPP_PATH");
  if (cpp == NULL)
	{
	  cpp = "/usr/bin/cpp";
	}
  char *cuasm = getenv("CUASM_PATH");
  if (cuasm == NULL)
	{
	  cuasm = "./cuasm_bg";
	}

  char outbuf[MAXCMD];
  Snprintf(outbuf, MAXCMD, "%s | %s", cpp, cuasm);
  FILE *out = Popen (outbuf, "w");

  // send command line over as the first line
  Fprintf (out, "\n");
  for (int i = 0; i < argc; i++)
	Fprintf (out, "%s ", argv[i]);
  Fprintf (out, "\n");

  char buf[MAXLINE];
  while (Fgets (buf, MAXLINE, infile) != NULL)
	{
	  Fputs (buf, out);
	}

  Pclose (out);

  if (infile != stdin)
	{
	  Fclose (infile);
	}

  return 0;
}

