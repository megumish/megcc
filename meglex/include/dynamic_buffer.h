#ifndef __MEGLEX_DYNAMIC_BUFFER_HEADER__
#define __MEGLEX_DYNAMIC_BUFFER_HEADER__
#include <stdio.h>
#include "pattern.h"

typedef struct DynamicBuffer
{
    char *buffer;
    size_t lexeme;
    size_t forward;
    int is_file_end;
    FILE *file;
    size_t buffer_max;
} DynamicBuffer;

int dynamic_buffer_init(DynamicBuffer *const dynamic_buffer, FILE *const file);

int dynamic_buffer_get_pattern(DynamicBuffer *const dynamic_buffer, Pattern *const pattern);

int dynamic_buffer_deinit(DynamicBuffer *const dynamic_buffer);

#endif
