#include "wrap.h"
#include "common.h"

FILE *ofile;
struct location location;

static int32_t next_seg  = 2;

int32_t seg_alloc(void)
{
  int32_t this_seg = next_seg;

  next_seg += 2;
  return this_seg;
}

void null_debug_init(void)
{
}

void null_debug_linenum(const char *filename, int32_t linenumber, int32_t segto)
{
  (void)filename;
  (void)linenumber;
  (void)segto;
}

void null_debug_deflabel(char *name, int32_t segment, int64_t offset,
                         int is_global, char *special)
{
  (void)name;
  (void)segment;
  (void)offset;
  (void)is_global;
  (void)special;
}

void null_debug_directive(const char *directive, const char *params)
{
  (void)directive;
  (void)params;
}

void null_reset(void)
{
  /* Nothing to do */
}

int32_t null_segbase(int32_t segment)
{
  return segment;
}

void null_debug_typevalue(int32_t type)
{
  (void)type;
}

void null_debug_output(int type, void *param)
{
  (void)type;
  (void)param;
}

void null_debug_cleanup(void)
{
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

const struct dfmt * const null_debug_arr[2] = { &null_debug_form, NULL };
/*
nasm_opt_val
nasm_do_legacy_output
nasm_signature_len

dfmt
dfmt_is_stabs
dfmt_is_dwarf

ofmt

stdscan_reset
stdscan_set
stdscan_get

is_simple

backend_label
fwritezero

// belong elsewhere

ol_seg_alloc
pass_first
evaluate
*/