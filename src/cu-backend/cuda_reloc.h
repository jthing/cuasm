/* List the relocation types for i386.  -*- C -*-
Copyright (C) 2000, 2001, 2002, 2003, 2005, 2009, 2015 Red Hat, Inc.
This file is part of elfutils.

This file is free software; you can redistribute it and/or modify
it under the terms of either

* the GNU Lesser General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at
your option) any later version

    or

* the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at
your option) any later version

    or both in parallel, as here.

elfutils is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

You should have received copies of the GNU General Public License and
the GNU Lesser General Public License along with this program.  If
    not, see <http://www.gnu.org/licenses/>.  */

/*          NAME,               REL|EXEC|DYN    */

#define R_TYPE(name)		PASTE (RELOC_PREFIX, name)
#define PASTE(a, b)		PASTE_1 (a, b)
#define PASTE_1(a, b)		a##b
#define R_NAME(name)		R_NAME_1 (RELOC_PREFIX, name)
#define R_NAME_1(prefix, type)	R_NAME_2 (prefix, type)
#define R_NAME_2(prefix, type)	#prefix #type

#define RELOC_TYPES		STRINGIFIED_PASTE (BACKEND, reloc.def)
#define STRINGIFIED_PASTE(a, b)	STRINGIFY (PASTE (a, b))
#define STRINGIFY(x)		STRINGIFY_1 (x)
#define STRINGIFY_1(x)		#x

#define	RELOC_TYPE(type, uses) \
  char name_##type[sizeof R_NAME (type)];

RELOC_TYPE (NONE,               0)
RELOC_TYPE (COPY,               EXEC|DYN)
RELOC_TYPE (32,                 REL|EXEC|DYN)
RELOC_TYPE (PC32,               REL|EXEC|DYN)
RELOC_TYPE (GOT32,              REL)
RELOC_TYPE (PLT32,              REL)
RELOC_TYPE (GLOB_DAT,           EXEC|DYN)
RELOC_TYPE (JMP_SLOT,           EXEC|DYN)
RELOC_TYPE (RELATIVE,           EXEC|DYN)
RELOC_TYPE (GOTOFF,             REL)
RELOC_TYPE (GOTPC,              REL)
RELOC_TYPE (32PLT,              REL)
RELOC_TYPE (TLS_TPOFF,          EXEC|DYN)
RELOC_TYPE (TLS_IE,             REL)
RELOC_TYPE (TLS_GOTIE,          REL)
RELOC_TYPE (TLS_LE,             REL)
RELOC_TYPE (TLS_GD,             REL)
RELOC_TYPE (TLS_LDM,            REL)
RELOC_TYPE (16,                 REL)
RELOC_TYPE (PC16,               REL)
RELOC_TYPE (8,                  REL)
RELOC_TYPE (PC8,                REL)
RELOC_TYPE (TLS_GD_32,          REL)
RELOC_TYPE (TLS_GD_PUSH,        REL)
RELOC_TYPE (TLS_GD_CALL,        REL)
RELOC_TYPE (TLS_GD_POP,         REL)
RELOC_TYPE (TLS_LDM_32,         REL)
RELOC_TYPE (TLS_LDM_PUSH,       REL)
RELOC_TYPE (TLS_LDM_CALL,       REL)
RELOC_TYPE (TLS_LDO_32,         REL)
RELOC_TYPE (TLS_IE_32,          REL)
RELOC_TYPE (TLS_LE_32,          REL)
RELOC_TYPE (TLS_DTPMOD32,       EXEC|DYN)
RELOC_TYPE (TLS_DTPOFF32,       EXEC|DYN)
RELOC_TYPE (TLS_TPOFF32,        EXEC|DYN)
RELOC_TYPE (TLS_GOTDESC,        REL)
RELOC_TYPE (TLS_DESC_CALL,      REL)
RELOC_TYPE (TLS_DESC,           EXEC)
RELOC_TYPE (IRELATIVE,          EXEC|DYN)
RELOC_TYPE (GOT32X,             REL)
