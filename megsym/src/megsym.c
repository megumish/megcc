#include "../include/megsym.h"
#include <stdlib.h>
#include <string.h>

#define TOKEN_LIST_MAX_SIZE 0x1000

const Token *const _token_list_at(const TokenNode *const node, const size_t count, const size_t index)
{
    if (count == index)
    {
        return &node->token;
    }
    return _token_list_at(node->next, count + 1, index);
}

const Token *const token_list_at(const TokenList *const token_list, const size_t index)
{
    if (index >= token_list->length)
    {
        return &INVALID_TOKEN;
    }
    return _token_list_at(token_list->node, 0, index);
}

size_t _token_list_append(TokenNode *const node, TokenNode *const new_node)
{
    if (!node->next)
    {
        node->next = new_node;
        return 1;
    }
    return _token_list_append(node->next, new_node) + 1;
}

int token_list_append(TokenList *const token_list, char *pattern, size_t pattern_length)
{
    TokenNode *new_node;
    if (!(new_node = calloc(sizeof(TokenNode), 1)))
    {
        puts("calloc failure");
        return 0;
    }
    Token *token = &new_node->token;
    Identifier *identifier;
    if (!(identifier = calloc(sizeof(Identifier), 1)))
    {
        puts("calloc failure");
        return 0;
    }
    char *pattern_copy = calloc(sizeof(char), pattern_length);
    memcpy(pattern_copy, pattern, pattern_length);
    identifier->id_str = pattern_copy;
    identifier->id_length = pattern_length;
    token->kind = TIdentifier;
    token->inner = identifier;
    if (!token_list->length)
    {
        token_list->node = new_node;
        token_list->length = 1;
        return 1;
    }
    size_t token_list_length = _token_list_append(token_list->node, new_node) + 1;
    if (token_list_length >= TOKEN_LIST_MAX_SIZE)
    {
        puts("too many token");
        return 0;
    }
    token_list->length = token_list_length;
    return 1;
}

void token_list_init(TokenList *const token_list)
{
    token_list->node = 0;
    token_list->length = 0;
}