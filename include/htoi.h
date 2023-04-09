//
// Created by john on 27.03.23.
//

#pragma once
#include <stdint.h>
#define hc2i(c) ((c) >= '0' && (c) <= '9' ? (c) - '0' : (c) - 'A')
uint64_t htoi(const char *ptr);