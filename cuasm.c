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

