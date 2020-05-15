#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/token.h"
#define Result TokenFactoryResult
#define Factory TokenFactory

int nothing_just_after_initialized();
int literal_integer();

int main(int argc, const char *const *const argv)
{
    if (argc <= 1)
    {
        puts("choose a test.\n");
        return -1;
    }

    const char *const sub_name = argv[1];
    if (!strcmp(sub_name, "nothing_just_after_initialized"))
    {
        return nothing_just_after_initialized();
    }
    if (!strcmp(sub_name, "literal_integer"))
    {
        return literal_integer();
    }
    printf("unknown test name");
    return -1;
}

int nothing_just_after_initialized()
{
    return -1;
}

int literal_integer()
{
    Pattern pattern;
    pattern.pattern_str = "123";
    pattern.pattern_length = 3;
    Factory factory;
    token_factory_init(&factory);
    token_factory_push_pattern(&factory, &pattern);
    Result result;
    token_factory_generate_token(&factory, &result);
    if (!result.is_right)
    {
        puts("token must be returned");
        return -1;
    }
    if (result.token.kind != TLiteralInteger)
    {
        puts("token must be literal integer");
        return -1;
    }
    if (result.token.unsigned_int != 123)
    {
        puts("token data is invalid");
        return -1;
    }
    token_factory_result_deinit(&result);
    token_factory_deinit(&factory);

    return 0;
}