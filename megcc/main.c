#include <stdio.h>
#include "meglex.h"
#include "megsym.h"

int main(const int argc, const char *const *const argv)
{
    if (argc <= 1)
    {
        puts("usage: megcc <FILE>");
        return -1;
    }

    FILE *const file = fopen(argv[1], "r");
    if (!file)
    {
        puts("can not open file");
        return -1;
    }

    Lexer lexer;
    lexer_init(&lexer, file);
    TokenList token_list;
    token_list_init(&token_list);
    if (!lexer_run(&lexer, &token_list))
    {
        puts("lexer error");
        return -1;
    }
    for (size_t i = 0; i < token_list.length; ++i)
    {
        const Token *token;
        char temp_buffer[0x100];
        if ((token = token_list_at(&token_list, i)) == &INVALID_TOKEN)
        {
            puts("token list out of range");
            return -1;
        }
        switch (token->kind)
        {
        case TIdentifier:
            sprintf(temp_buffer, "Token: %%.%zus\n", ((Identifier *)token->inner)->id_length);
            printf(temp_buffer, ((Identifier *)token->inner)->id_str);
            break;
        default:
            puts("invalid token kind");
            return -1;
        }
    }
    fclose(file);
    return 0;
}
