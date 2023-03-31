/* cuda assembler

Copyright 2023 Pandora Norge

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

#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "htoi.h"

#define NIBBLES_IN_U64 16

int check_hex(const char *ptr)
{
    for (int i = 1; i < NIBBLES_IN_U64; i++) {
        if (!isxdigit(ptr[i])) {
            return 0;
        }
    }
    return 1;
}

uint64_t htoi(const char *ptr)
{
    assert(ptr && strlen(ptr) == 16);
    assert(check_hex(ptr));

    uint64_t value = 0;
    for (int i = 0; i < NIBBLES_IN_U64; i++) {
        uint8_t ch = ptr[i] >= '0' && ptr[i] <= '9' ? ptr[i] - '0' : ptr[i] - 'A';
        value += ch;
        value <<= 4;
    }
    return value;
}
