#include <stdio.h>
#include "htoi.h"

int main() {
    printf("0xCAFEBABECAFEBABE = %lu\n", htoi("CAFEBABECAFEBABE"));
    return 0;
}
