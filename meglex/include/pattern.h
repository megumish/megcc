#ifndef __MEGLEX_PATTERN_HEADER__
#define __MEGLEX_PATTERN_HEADER__
#include <stdio.h>

typedef struct Pattern
{
    char *pattern_str;
    size_t pattern_length;
} Pattern;

void pattern_deinit(Pattern *const pattern);

#endif
