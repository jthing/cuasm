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
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <libgen.h>
#include <errno.h>
#include "htoi.h"
#include "utils.h"
#include "wrap.h"

int main ()
{
  if (isatty (STDIN_FILENO))
    {
      fprintf (stderr, "PLEASE PIPE ME!!.\n");
      exit (1);
    }

  FILE *in_file = stdin;

  char buf[MAXLINE + 1];

  // CPP prints a bunch of lines starting with #... throw them away
  while (Fgets (buf, MAXLINE + 1, in_file) != NULL)
    if (buf[0] != '#')
      break;

  // cuasm transfers its parameters as one line
  char cmd[MAXLINE + 1];
  if (Fgets (buf, MAXLINE + 1, in_file) != NULL)
    {
      char *ln = ws_strip (buf);
      strncpy (cmd, ln, MAXLINE);
    }

  // cmdc, cmdv is now cuasm's argc, argv
  int cmdc = 0;
  char **cmdv = parse_cmd (cmd, &cmdc);

  char *outfile = "elf.o";
  int c;
  while ((c = getopt (cmdc, cmdv, "o:")) != -1)
    switch (c)
      {
        case 'o':
          outfile = optarg;
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
          abort ();
      }

  // write to output file
  FILE *out;
  if ((out = fopen (outfile, "w")) == NULL)
    {
      perror (basename (cmdv[0]));
      exit (errno);
    }

  // Finally process the .asm file
  while (Fgets (buf, MAXLINE + 1, in_file) != NULL)
    {
      char *ln = ws_strip (buf);
      Fprintf (out, "%s = %lu\n", ln, htoi (ln));
    }

  if (out != stdout)
    Fclose (out);

  return 0;
}
