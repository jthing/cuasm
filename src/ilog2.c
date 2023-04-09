#include "wrap.h"
#include "ilog2.h"

uint ilog2_32(uint32_t v)
{
  unsigned int n;

  __asm__("bsrl %1,%0"
      : "=r" (n)
      : "rm" (v), "0" (0));
  return n;
}

uint ilog2_64(uint64_t vv)
{
  unsigned int p = 0;
  uint32_t v;

  v = vv >> 32;
  if (v)
    p += 32;
  else
    v = vv;

  return p + ilog2_32 (v);
}

/*
 * v == 0 ? 0 : is_power2(x) ? ilog2_X(v) : -1
 */
uint alignlog2_32(uint32_t v)
{
  if (unlikely(v & (v-1)))
    return -1;              /* invalid alignment */

  return ilog2_32(v);
}

inline uint alignlog2_64(uint64_t v)
{
  if (unlikely(v & (v-1)))
    return -1;              /* invalid alignment */

  return ilog2_64(v);
}

//
// Created by john on 09.04.23.
//
