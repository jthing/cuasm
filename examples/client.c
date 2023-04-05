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
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include "wrap/wrap.h"

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

  char buf[MAXLINE];
  while (Fgets (buf, MAXLINE, infile) != NULL)
	{
	  Fputs (buf, out);
	}

  Fclose (infile);
  Pclose (out);

  return 0;
}
