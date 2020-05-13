#ifndef __MEGLEX_HEADER__
#define __MEGLEX_HEADER__
#include <stdio.h>
#include "megsym.h"
#include "dynamic_buffer.h"

#define BUFFER_SIZE 0x1000

typedef struct Lexer
{
    char buffer[0x1000];
    FILE *file;
} Lexer;

void lexer_init(Lexer *const lexer, FILE *const file);

int lexer_run(Lexer *const lexer, TokenList *const tokens);

#endif
