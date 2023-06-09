#include <elf.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>

#define BACKEND cuda_
#include "elfutils/lib/eu-config.h"
#include "elfutils/libasm/libasm.h"
#include "elfutils/backends/libebl_CPU.h"

static const Ebl_Register_Location prstatus_regs[] =
{
#define GR(at, n, dwreg)                                                \
    { .offset = at * 4, .regno = dwreg, .count = n, .bits = 32 }
#define SR(at, n, dwreg)                                                \
    { .offset = at * 4, .regno = dwreg, .count = n, .bits = 16, .pad = 2 }

GR (0, 1, 3),               /* %ebx */
GR (1, 2, 1),               /* %ecx-%edx */
GR (3, 2, 6),               /* %esi-%edi */
GR (5, 1, 5),               /* %ebp */
GR (6, 1, 0),               /* %eax */
SR (7, 1, 43),              /* %ds */
SR (8, 1, 40),              /* %es */
SR (9, 1, 44),              /* %fs */
SR (10, 1, 45),             /* %gs */
/*  11, 1,                     orig_eax */
GR (12, 1, 8),              /* %eip */
SR (13, 1, 41),             /* %cs */
GR (14, 1, 9),              /* eflags */
GR (15, 1, 4),              /* %esp */
SR (16, 1, 42),             /* %ss */

#undef  GR
#undef  SR
};
#define PRSTATUS_REGS_SIZE      (17 * 4)

#define ULONG                   uint32_t
#define PID_T                   int32_t
#define UID_T                   uint16_t
#define GID_T                   uint16_t
#define ALIGN_ULONG             4
#define ALIGN_PID_T             4
#define ALIGN_UID_T             2
#define ALIGN_GID_T             2
#define TYPE_ULONG              ELF_T_WORD
#define TYPE_PID_T              ELF_T_SWORD
#define TYPE_UID_T              ELF_T_HALF
#define TYPE_GID_T              ELF_T_HALF

#define PRSTATUS_REGSET_ITEMS                                                 \
  {                                                                           \
    .name = "orig_eax", .type = ELF_T_SWORD, .format = 'd',                   \
    .offset = offsetof (struct EBLHOOK(prstatus), pr_reg) + (4 * 11),         \
    .group = "register"                                                       \
  }

static const Ebl_Register_Location fpregset_regs[] =
    {
        { .offset = 0, .regno = 37, .count = 2, .bits = 32 }, /* fctrl-fstat */
        { .offset = 7 * 4, .regno = 11, .count = 8, .bits = 80 }, /* stN */
    };
#define FPREGSET_SIZE   108

static const Ebl_Register_Location prxfpreg_regs[] =
    {
        { .offset = 0, .regno = 37, .count = 2, .bits = 16 }, /* fctrl-fstat */
        { .offset = 24, .regno = 39, .count = 1, .bits = 32 }, /* mxcsr */
        { .offset = 32, .regno = 11, .count = 8, .bits = 80, .pad = 6 }, /* stN */
        { .offset = 32 + 128, .regno = 21, .count = 8, .bits = 128 }, /* xmm */
    };

#define PRSTATUS_REGS_SIZE      (17 * 4)

#define ULONG                   uint32_t
#define PID_T                   int32_t
#define UID_T                   uint16_t
#define GID_T                   uint16_t
#define ALIGN_ULONG             4
#define ALIGN_PID_T             4
#define ALIGN_UID_T             2
#define ALIGN_GID_T             2
#define TYPE_ULONG              ELF_T_WORD
#define TYPE_PID_T              ELF_T_SWORD
#define TYPE_UID_T              ELF_T_HALF
#define TYPE_GID_T              ELF_T_HALF

#define PRSTATUS_REGSET_ITEMS                                                 \
  {                                                                           \
    .name = "orig_eax", .type = ELF_T_SWORD, .format = 'd',                   \
    .offset = offsetof (struct EBLHOOK(prstatus), pr_reg) + (4 * 11),         \
    .group = "register"                                                       \
  }

#define EXTRA_NOTES_IOPERM
#define FPREGSET_SIZE   108

#define EXTRA_NOTES \
  EXTRA_REGSET (NT_PRXFPREG, 512, prxfpreg_regs) \
  case NT_386_TLS: \
    return tls_info (nhdr->n_descsz, regs_offset, nregloc, reglocs, \
                     nitems, items);                                \
  EXTRA_NOTES_IOPERM

static const Ebl_Core_Item tls_items[] =
    {
        { .type = ELF_T_WORD, .offset = 0x0, .format = 'd', .name = "index" },
        { .type = ELF_T_WORD, .offset = 0x4, .format = 'x', .name = "base" },
        { .type = ELF_T_WORD, .offset = 0x8, .format = 'x', .name = "limit" },
        { .type = ELF_T_WORD, .offset = 0xc, .format = 'x', .name = "flags" },
    };

static int tls_info (GElf_Word descsz, GElf_Word *regs_offset,
                     size_t *nregloc, const Ebl_Register_Location **reglocs,
                     size_t *nitems, const Ebl_Core_Item **items)
{
  if (descsz % 16 != 0)
    return 0;

  *regs_offset = 0;
  *nregloc = 0;
  *reglocs = NULL;
  *nitems = sizeof tls_items / sizeof tls_items[0];
  *items = tls_items;
  return 1;
}

//#include "cuda_corenote.c"
#include "linux-core-note.c"