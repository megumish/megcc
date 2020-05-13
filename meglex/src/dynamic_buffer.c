#include "../include/dynamic_buffer.h"
#include "../include/pattern.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define APPEND_BUFFER_SIZE 0x1000

int dynamic_buffer_init(DynamicBuffer *const dynamic_buffer, FILE *const file)
{
    dynamic_buffer->forward = 0;
    dynamic_buffer->lexeme = 0;
    dynamic_buffer->buffer = calloc(APPEND_BUFFER_SIZE, sizeof(char));
    if (!dynamic_buffer->buffer)
    {
        puts("calloc failure");
        return 0;
    }
    dynamic_buffer->file = file;
    size_t last = fread(dynamic_buffer->buffer, sizeof(char), APPEND_BUFFER_SIZE, dynamic_buffer->file);
    if (last < APPEND_BUFFER_SIZE)
    {
        dynamic_buffer->buffer[last] = 0;
    }
    dynamic_buffer->is_file_end = 0;
    dynamic_buffer->buffer_max = APPEND_BUFFER_SIZE;
    return 1;
}

int dynamic_buffer_copy_pattern(DynamicBuffer *dynamic_buffer, Pattern *pattern, InQuote in_quote)
{
    pattern->in_quote = in_quote;
    pattern->pattern_str = strndup(dynamic_buffer->buffer + dynamic_buffer->lexeme, dynamic_buffer->forward - dynamic_buffer->lexeme);
    if (!pattern->pattern_str)
    {
        puts("strdup failed");
        return 0;
    }
    pattern->pattern_length = dynamic_buffer->forward - dynamic_buffer->lexeme;
    ++dynamic_buffer->forward;
    dynamic_buffer->lexeme = dynamic_buffer->forward;
    return 1;
}

int dynamic_buffer_get_pattern(DynamicBuffer *const dynamic_buffer, Pattern *const pattern)
{
    if (dynamic_buffer->is_file_end)
    {
        puts("file");
        return 0;
    }
    InQuote in_quote = QOut;
    while (1)
    {
        if (dynamic_buffer->forward == dynamic_buffer->buffer_max)
        {
            char *const new_buffer = calloc(dynamic_buffer->forward + APPEND_BUFFER_SIZE, sizeof(char));
            if (!new_buffer)
            {
                puts("calloc failed");
                return 0;
            }
            memcpy(new_buffer, dynamic_buffer->buffer, sizeof(char) * (dynamic_buffer->forward + APPEND_BUFFER_SIZE));
            free(dynamic_buffer->buffer);
            dynamic_buffer->buffer = new_buffer;
            size_t last = fread(dynamic_buffer->buffer + dynamic_buffer->forward, sizeof(char), APPEND_BUFFER_SIZE, dynamic_buffer->file);
            printf("%s\n", dynamic_buffer->buffer);
            if (last < APPEND_BUFFER_SIZE)
            {
                dynamic_buffer->buffer[last + dynamic_buffer->forward] = 0;
            }
            dynamic_buffer->buffer_max = dynamic_buffer->forward + APPEND_BUFFER_SIZE;
            continue;
        }

        if (!dynamic_buffer->buffer[dynamic_buffer->forward])
        {
            dynamic_buffer->is_file_end = 1;
            if (in_quote != QOut)
            {
                puts("reached EOF in quote");
                return 0;
            }
            return dynamic_buffer_copy_pattern(dynamic_buffer, pattern, in_quote);
        }

        switch (in_quote)
        {
        case QOut:
            if (dynamic_buffer->buffer[dynamic_buffer->forward] == '\'')
            {
                in_quote = QSingleQuote;
                ++dynamic_buffer->lexeme;
            }
            if (dynamic_buffer->buffer[dynamic_buffer->forward] == '"')
            {
                in_quote = QDoubleQuote;
                ++dynamic_buffer->lexeme;
            }
            if (dynamic_buffer->buffer[dynamic_buffer->forward] == ' ' || dynamic_buffer->buffer[dynamic_buffer->forward] == '\n')
            {
                if (dynamic_buffer->forward == dynamic_buffer->lexeme)
                {
                    ++dynamic_buffer->forward;
                    ++dynamic_buffer->lexeme;
                    continue;
                }
                return dynamic_buffer_copy_pattern(dynamic_buffer, pattern, in_quote);
            }
            break;
        case QSingleQuote:
            if (dynamic_buffer->buffer[dynamic_buffer->forward] == '\'')
            {
                return dynamic_buffer_copy_pattern(dynamic_buffer, pattern, in_quote);
            }
            break;
        case QDoubleQuote:
            if (dynamic_buffer->buffer[dynamic_buffer->forward] == '"')
            {
                return dynamic_buffer_copy_pattern(dynamic_buffer, pattern, in_quote);
            }
            break;
        }
        ++dynamic_buffer->forward;
    }
}

int dynamic_buffer_deinit(DynamicBuffer *const dynamic_buffer)
{
    dynamic_buffer->lexeme = 0;
    dynamic_buffer->forward = 0;
    dynamic_buffer->is_file_end = 1;
    free(dynamic_buffer->buffer);
    if (fclose(dynamic_buffer->file) == EOF)
    {
        puts("failed to file closing");
        return 0;
    }
    return 1;
}