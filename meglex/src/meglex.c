#include "../include/meglex.h"
#include "megsym.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IDENTIFIER_MAX_SIZE 0x100

typedef struct _Invalid
{
} _Invalid;

const _Invalid _INVALID;
const Token INVALID_TOKEN = {TInvalid, (void *const) & _INVALID};

void buffer_init(char *const buffer, FILE *const file)
{
    size_t last = fread(buffer, sizeof(char), (BUFFER_SIZE / 2) - 1, file);
    for (size_t i = 0; i < last - 1; ++i)
    {
        if (!buffer[i])
        {
            buffer[i] = ' ';
        }
    }
    buffer[last] = 0;
}

void lexer_init(Lexer *const lexer, FILE *const file)
{
    lexer->file = file;
    buffer_init(lexer->buffer, lexer->file);
}

int lexer_run(Lexer *const lexer, TokenList *const token_list)
{
    size_t lexeme = 0;
    size_t forward = 0;
    char temporal_buffer[IDENTIFIER_MAX_SIZE];
    memset(temporal_buffer, 0, IDENTIFIER_MAX_SIZE);
    size_t temporal_buffer_length = 0;
    while (1)
    {
        if (forward == BUFFER_SIZE - 1)
        {
            buffer_init(lexer->buffer, lexer->file);
            if (forward - lexeme > IDENTIFIER_MAX_SIZE)
            {
                puts("too long identifier");
                return 0;
            }
            strncpy(temporal_buffer, lexer->buffer + lexeme, forward - lexeme);
            temporal_buffer_length = forward - lexeme;
            temporal_buffer[temporal_buffer_length] = 0;
            forward = 0;
            continue;
        }
        if (!lexer->buffer[forward])
        {
            if (forward != (BUFFER_SIZE / 2) - 1)
            {
                char *pattern;
                size_t pattern_length;
                if (lexeme > forward)
                {
                    if (temporal_buffer_length + lexeme > IDENTIFIER_MAX_SIZE)
                    {
                        puts("too long identifier");
                        return 0;
                    }
                    pattern = strncat(temporal_buffer, lexer->buffer + forward, lexeme);
                    pattern_length = lexeme;
                }
                else
                {
                    pattern = lexer->buffer + lexeme;
                    pattern_length = forward - lexeme;
                }
                if ((forward - lexeme) > IDENTIFIER_MAX_SIZE)
                {
                    puts("too long identifier");
                    return 0;
                }
                token_list_append(token_list, pattern, pattern_length);
                return 1;
            }
            buffer_init(lexer->buffer + (BUFFER_SIZE / 2), lexer->file);
            strncpy(temporal_buffer, lexer->buffer + lexeme + 1, forward - lexeme);
            temporal_buffer_length = forward - lexeme;
            temporal_buffer[temporal_buffer_length] = 0;
            ++forward;
            continue;
        }
        if (lexer->buffer[forward] == ' ' || lexer->buffer[forward] == '\n')
        {
            char *pattern;
            size_t pattern_length;
            if (lexeme > forward)
            {
                if (temporal_buffer_length + forward > IDENTIFIER_MAX_SIZE)
                {
                    puts("too long identifier");
                    return 0;
                }
                pattern = strncat(temporal_buffer, lexer->buffer, forward);
                pattern_length = temporal_buffer_length + forward;
            }
            else
            {
                pattern = strncat(temporal_buffer, lexer->buffer + lexeme, forward - lexeme);
                pattern_length = temporal_buffer_length + forward - lexeme;
                printf("%s\n", temporal_buffer);
                if ((forward - lexeme) > IDENTIFIER_MAX_SIZE)
                {
                    puts("too long identifier");
                    return 0;
                }
            }
            token_list_append(token_list, pattern, pattern_length);
            memset(temporal_buffer, 0, IDENTIFIER_MAX_SIZE);
            temporal_buffer_length = 0;
            lexeme = forward + 1;
        }
        ++forward;
    }
}
