#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <libelf.h>
#include "wrap.h"

#define R_CUDA_GOTPC 1
#define R_CUDA_64 64
#define R_CUDA_32 32
#define R_CUDA_16 16
#define R_CUDA_8   8

#define BACKEND CUDA_
#include "elfutils/libebl/libebl.h"

/**
 * Return true is the symbol type references the GOT.
 * @param ebl
 * @param type
 * @param addsub
 * @return
 */
bool cuda_gotpc_reloc_check(Elf *ebl , int type, int *addsub)
{
  return type == R_CUDA_GOTPC;
}

/**
 * Check for the simple reloc types.
 * @param ebl
 * @param type
 * @param addsub
 * @return
 */
Elf_Type cuda_reloc_simple_type(Ebl *ebl, int type, int *addsub)
{
  switch (type)
    {
      case R_CUDA_64:
        return ELF_T_WORD;
      case R_CUDA_32:
        return ELF_T_SWORD;
      case R_CUDA_16:
        return ELF_T_HALF;
      case R_CUDA_8:
        return ELF_T_BYTE;
      default:
        return ELF_T_NUM;
    }
}

/**
 * Check is the section name is a debug section.
 * @return
 */
extern bool (*generic_debugscn_p) (const char *);
bool cuda_debugscn_p (const char *name)
{
  return (generic_debugscn_p (name)
  || strcmp (name, ".stab") == 0
  || strcmp (name, ".stabstr") == 0);
}

