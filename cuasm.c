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
#include <ctype.h>
#include "htoi.h"
#include "wrap.h"

#define MAXLINE 1024

/**
 * \brief whitespace back strip
 *
 * buf is scanned from the back and a '\0' inserted after the last non whitespace character.
 * @param buf - *buf modified
 */
void ws_bstrip (char *buf)
{
  size_t j = strlen (buf) - 1;
  while (!isspace(buf[j]))
	{
	  --j;
	}
  buf[j] = '\0';
}

/**
 * \brief whitespace front strip
 *
 * buf is scanned from the front past leading whitepspace
 * @param buf
 * @return - points to the first non-space character in buf
 */
char *ws_fstrip (char *buf)
{
  size_t i = 0;
  while (isspace(buf[i]))
	{
	  ++i;
	}
  return &buf[i];
}

/**
 * \brief strips leading and trailing whitespace
 *
 * \see ws_fstrip,  ws_bstrip
 * @param buf
 * @return - points to the frist nonspace character in buf
 */
char * ws_strip(char *buf)
{
  char *ln = ws_fstrip(buf);
  ws_bstrip(ln);
  return ln;
}

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
	  if (buf[0] == '#' || buf[0] == '\n')
		{
		  continue;
		}
	  char *ln = ws_strip(buf);
	  Printf ("%s = %lu\n", ln, htoi (ln));
	}

  if (in_file != stdin)
	{
	  Fclose (in_file);
	}

  return 0;
}

