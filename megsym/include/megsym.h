#ifndef __MEGSYM_HEADER__
#define __MEGSYM_HEADER__
#include <stdio.h>

typedef enum TokenKind
{
    TIdentifier,
    TInvalid,
} TokenKind;

typedef struct Token
{
    TokenKind kind;
    void *inner;
} Token;

typedef struct TokenNode
{
    Token token;
    struct TokenNode *next;
} TokenNode;

typedef struct TokenList
{
    TokenNode *node;
    size_t length;
} TokenList;

typedef struct Identifier
{
    char *id_str;
    size_t id_length;
} Identifier;

const Token INVALID_TOKEN;

const Token *const token_list_at(const TokenList *const tokens, const size_t index);

int token_list_append(TokenList *const token_list, char *pattern, size_t patter_length);

void token_list_init(TokenList *const token_list);
#endif
