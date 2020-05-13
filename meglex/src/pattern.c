#include "../include/pattern.h"
#include <stdlib.h>

void pattern_deinit(Pattern *const pattern)
{
    pattern->pattern_length = 0;
    free(pattern->pattern_str);
}