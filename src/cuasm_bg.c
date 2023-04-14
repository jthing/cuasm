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

#include "elfutils/libasm/libasm.h"
#include "elfutils/libebl/libebl.h"
#include <libelf.h>
#include <elf.h>

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

  AsmCtx_t *ctx;
  AsmScn_t *scn1;
  AsmScn_t *scn2;

  elf_version (EV_CURRENT);

  Ebl *ebl = ebl_openbackend_machine (EM_CUDA);
  if (ebl == NULL)
    {
      Fputs ("cannot open backend library", stderr);
      return 1;
    }

  ctx = asm_begin (outfile, ebl, false);
  if (ctx == NULL)
    {
      Fprintf (stderr, "cannot create assembler context: %s\n", asm_errmsg (-1));
      return 1;
    }

  // Create two sections.
  scn1 = asm_newscn (ctx, ".text", SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR);
  scn2 = asm_newscn (ctx, ".data", SHT_PROGBITS, SHF_ALLOC | SHF_WRITE);
  if (scn1 == NULL || scn2 == NULL)
    {
      Fprintf (stderr, "cannot create section in output file: %s\n", asm_errmsg (-1));
      asm_abort (ctx);
      return 1;
    }

  // Special alignment for the .text section.
  if (asm_align (scn1, 32) != 0)
    {
      Fprintf (stderr, "cannot align .text section: %s\n", asm_errmsg (-1));
      return 1;
    }

  // Create the output file.
  if (asm_end (ctx) != 0)
    {
      Fprintf (stderr, "cannot create output file: %s\n", asm_errmsg (-1));
      asm_abort (ctx);
      return 1;
    }

  ebl_closebackend (ebl);

  return 0;
}
