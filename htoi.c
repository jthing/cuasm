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
