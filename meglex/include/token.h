#ifndef __MEGLEX_TOKEN_HEADER__
#define __MEGLEX_TOKEN_HEADER__
#include <stdio.h>
#include "pattern.h"

typedef enum TokenKind
{
    TLiteralInteger,
} TokenKind;

typedef struct Token
{
    TokenKind kind;
    union {
        size_t unsigned_int;
    };
} Token;

typedef struct TokenFactory
{
} TokenFactory;

typedef struct TokenFactoryError
{
} TokenFactoryError;

typedef struct TokenFactoryResult
{
    int is_right;
    union {
        TokenFactoryError error;
        Token token;
    };
} TokenFactoryResult;

void token_factory_init(TokenFactory *const factory);

void token_factory_deinit(TokenFactory *const factory);

void token_factory_push_pattern(TokenFactory *const factory, const Pattern *const pattern);

void token_factory_generate_token(TokenFactory *const factory, TokenFactoryResult *const result);

void token_factory_result_deinit(TokenFactoryResult *const result);

#endif