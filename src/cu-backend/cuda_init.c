

#define BACKEND cuda_
#define RELOC_PREFIX R_cuda_
#include "elfutils/libebl/libebl.h"
#include "elfutils/libasm/libasm.h"
#include "elfutils/libebl/libeblP.h"
#include "elfutils/backends/libebl_CPU.h"

#include "cuda_reloc.h"
//#include "elfutils/backends/common-reloc.c"

void cuda_init_reloc (Ebl *p_ebl)
{

}

extern Elf_Type cuda_reloc_simple_type(Ebl *pEbl, int i, int *pInt);

extern bool cuda_gotpc_reloc_check(Elf *pElf, int i);

extern int cuda_core_note(const GElf_Nhdr *ptr, const char *string, GElf_Word *pInt, size_t *pInt1,
                          const Ebl_Register_Location **ptr1, size_t *pInt2, const Ebl_Core_Item **ptr2);

extern bool cuda_debugscn_p(const char *string);

int cuda_return_value_location(Dwarf_Die *ptr, const Dwarf_Op **ptr1)
{

}

ssize_t cuda_register_info(Ebl *pEbl, int i, char *string, size_t i1,
                           const char **pString, const char **pString1, int *pInt, int *pInt1)
{

}

int cuda_auxv_info(GElf_Xword i, const char **pString, const char **pString1)
{

}

int cuda_disasm(Ebl *pEbl, const uint8_t **pString, const uint8_t *string, GElf_Addr i,
                const char *string1, DisasmOutputCB_t i1, DisasmGetSymCB_t i2, void *pVoid, void *pVoid1)
{

}

int cuda_abi_cfi(Ebl *pEbl, Dwarf_CIE *ptr)
{

}

bool cuda_set_initial_registers_tid(pid_t i, ebl_tid_registers_t (*pFunction), void *pVoid)
{

}

bool cuda_unwind(Ebl *pEbl, Dwarf_Addr i, ebl_tid_registers_t (*pFunction),
                 ebl_tid_registers_get_t (*pFunction1), ebl_pid_memory_read_t (*pFunction2),
                 void *pVoid, bool *pBoolean)
{

}

Ebl * cuda_init(Elf *elf __attribute__ ((unused)),
                GElf_Half machine __attribute__ ((unused)),
                Ebl *eh)
{
  cuda_init_reloc(eh);
  HOOK (eh, reloc_simple_type);
  HOOK (eh, gotpc_reloc_check);
  HOOK (eh, core_note);
  generic_debugscn_p = eh->debugscn_p;
  HOOK (eh, debugscn_p);
  HOOK (eh, return_value_location);
  HOOK (eh, register_info);
  HOOK (eh, auxv_info);
  HOOK (eh, disasm);
  HOOK (eh, abi_cfi);
  eh->frame_nregs = 255;
  HOOK (eh, set_initial_registers_tid);
  HOOK (eh, unwind);

  return eh;
}
