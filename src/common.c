#include "wrap.h"
#include "common.h"

FILE *ofile;
struct location location;

static int32_t next_seg = 2;

int32_t seg_alloc (void)
{
  int32_t this_seg = next_seg;

  next_seg += 2;
  return this_seg;
}

void null_debug_init (void)
{
}

void null_debug_linenum (const char *filename, int32_t linenumber, int32_t segto)
{
  (void) filename;
  (void) linenumber;
  (void) segto;
}

void null_debug_deflabel (char *name, int32_t segment, int64_t offset,
                          int is_global, char *special)
{
  (void) name;
  (void) segment;
  (void) offset;
  (void) is_global;
  (void) special;
}

void null_debug_directive (const char *directive, const char *params)
{
  (void) directive;
  (void) params;
}

void null_reset (void)
{
  /* Nothing to do */
}

int32_t null_segbase (int32_t segment)
{
  return segment;
}

void null_debug_typevalue (int32_t type)
{
  (void) type;
}

void null_debug_output (int type, void *param)
{
  (void) type;
  (void) param;
}

void null_debug_cleanup (void)
{
}

int pass_first ()
{
  return 1;
}

const struct dfmt null_debug_form = {
    "Null",
    "null",
    null_debug_init,
    null_debug_linenum,
    null_debug_deflabel,
    NULL,                       /* .debug_smacros */
    NULL,                       /* .debug_include */
    NULL,                       /* .debug_mmacros */
    null_debug_directive,
    null_debug_typevalue,
    null_debug_output,
    null_debug_cleanup,
    NULL                        /* pragma list */
};

const struct dfmt *const null_debug_arr[2] = {&null_debug_form, NULL};
struct dfmt *dfmt = (struct dfmt *) &null_debug_form;
const struct ofmt *ofmt;

bool reproducible = false;
#define NASM_VER "2.17rc0"

static const char *const _nasm_signature[2] = {
    "NASM " NASM_VER,
    "NASM"
};

const char *nasm_signature (void)
{
  return _nasm_signature[reproducible];
}

size_t nasm_signature_len (void)
{
  return strlen (nasm_signature ());
}

void fwritezero (size_t bytes, FILE *fp)
{}

#define p_define                 226
#define p_macro                  232
#define p_endmacro               199
#define p_imacro                 233
#define EOL                      127

const unsigned char elf_stdmac[] = {
    /* From ./output/outelf.mac */
    /*    0 */ p_define, '_', '_', '?', 'S', 'E', 'C', 'T', '?', '_', '_', ' ', '[', 's', 'e', 'c', 't', 'i', 'o', 'n',
               ' ', '.', 't', 'e', 'x', 't', ']', EOL,
    /*   28 */ p_macro, '_', '_', '?', 'N', 'A', 'S', 'M', '_', 'C', 'D', 'e', 'c', 'l', '?', '_', '_', ' ', '1', EOL,
    /*   48 */ p_define, '$', '_', '%', '1', ' ', '$', '%', '1', EOL,
    /*   58 */ p_endmacro, EOL,
    /*   60 */ p_imacro, 'o', 's', 'a', 'b', 'i', ' ', '1', '+', '.', 'n', 'o', 'l', 'i', 's', 't', EOL,
    /*   77 */ '[', '%', '?', ' ', '%', '1', ']', EOL,
    /*   85 */ p_endmacro, EOL,
    /*   87 */ EOL
};

const uint8_t zero_buffer[ZERO_BUF_SIZE];

/*
* Standard scanner routine used by parser.c and some output
* formats. It keeps a succession of temporary-storage strings in
    * stdscan_tempstorage, which can be cleared using stdscan_reset.
*/
static char *stdscan_bufptr = NULL;
static char **stdscan_tempstorage = NULL;
static int stdscan_tempsize = 0, stdscan_templen = 0;
#define STDSCAN_TEMP_DELTA 256

void stdscan_set (char *str)
{
  stdscan_bufptr = str;
}

char *stdscan_get (void)
{
  return stdscan_bufptr;
}
static void stdscan_pop (void)
{
  free (stdscan_tempstorage[--stdscan_templen]);
}

void stdscan_reset (void)
{
  while (stdscan_templen > 0)
    stdscan_pop ();
}
