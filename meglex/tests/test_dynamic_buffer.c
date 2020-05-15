#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/dynamic_buffer.h"
#include "../include/pattern.h"

int a_char();
int two_chars();
int too_many_chars();
int marks();

int main(int argc, const char *const *const argv)
{
    if (argc <= 1)
    {
        puts("choose a test.\n");
        return -1;
    }

    const char *const sub_name = argv[1];
    if (!strcmp(sub_name, "a_char"))
    {
        return a_char();
    }
    if (!strcmp(sub_name, "two_chars"))
    {
        return two_chars();
    }
    if (!strcmp(sub_name, "too_many_chars"))
    {
        return too_many_chars();
    }
    if (!strcmp(sub_name, "marks"))
    {
        return marks();
    }
    puts("parse shite yaruyo...");

    FILE *file = fopen(sub_name, "r");
    if (!file)
    {
        puts("can not open file");
        return -1;
    }
    DynamicBuffer buffer;
    // move file owner to buffer
    if (!dynamic_buffer_init(&buffer, file))
    {
        puts("failed to initialize dynamic buffer");
        return -1;
    }
    while (!buffer.is_file_end)
    {
        Pattern pattern;
        if (!dynamic_buffer_get_pattern(&buffer, &pattern))
        {
            puts("can not get pattern");
            return -1;
        }
        printf("pattern: %s\n", pattern.pattern_str);
        printf("pattern_length: %zu\n", pattern.pattern_length);
        pattern_deinit(&pattern);
    }

    if (!buffer.is_file_end)
    {
        puts("file must be ended, but has been enable to read");
        return -1;
    }
    if (!dynamic_buffer_deinit(&buffer))
    {
        puts("failed to deinittialize dynamic buffer");
        return -1;
    }
    return -1;
}

int a_char()
{
    puts("Start test 'a_char'");
    FILE *file = fopen("./a_char.txt", "r");
    if (!file)
    {
        puts("can not open file");
        return -1;
    }
    DynamicBuffer buffer;
    // move file owner to buffer
    if (!dynamic_buffer_init(&buffer, file))
    {
        puts("failed to initialize dynamic buffer");
        return -1;
    }
    Pattern pattern;
    if (!dynamic_buffer_get_pattern(&buffer, &pattern))
    {
        puts("can not get pattern");
        return -1;
    }
    printf("pattern: %s\n", pattern.pattern_str);
    printf("pattern_length: %zu\n", pattern.pattern_length);
    if (strncmp(pattern.pattern_str, "A", pattern.pattern_length) || pattern.pattern_length != 1)
    {
        puts("incorrect pattern");
        return -1;
    }

    if (!buffer.is_file_end)
    {
        puts("file must be ended, but has been enable to read");
        return -1;
    }
    pattern_deinit(&pattern);
    if (!dynamic_buffer_deinit(&buffer))
    {
        puts("failed to deinittialize dynamic buffer");
        return -1;
    }
    return 0;
}

int two_chars()
{
    puts("Start test 'two_chars'");
    FILE *file = fopen("./two_chars.txt", "r");
    if (!file)
    {
        puts("can not open file");
        return -1;
    }
    DynamicBuffer buffer;
    // move file owner to buffer
    if (!dynamic_buffer_init(&buffer, file))
    {
        puts("failed to initialize dynamic buffer");
        return -1;
    }
    Pattern pattern0;
    if (!dynamic_buffer_get_pattern(&buffer, &pattern0))
    {
        puts("can not get pattern0");
        return -1;
    }
    Pattern pattern1;
    if (!dynamic_buffer_get_pattern(&buffer, &pattern1))
    {
        puts("can not get pattern1");
        return -1;
    }

    printf("pattern0: %s\n", pattern0.pattern_str);
    printf("pattern0_length: %zu\n", pattern0.pattern_length);
    if (strncmp(pattern0.pattern_str, "A", pattern0.pattern_length) || pattern0.pattern_length != 1)
    {
        puts("incorrect pattern0");
        return -1;
    }
    printf("pattern1: %s\n", pattern1.pattern_str);
    printf("pattern1_length: %zu\n", pattern1.pattern_length);
    if (strncmp(pattern1.pattern_str, "B", pattern1.pattern_length) || pattern1.pattern_length != 1)
    {
        puts("incorrect pattern1");
        return -1;
    }

    if (!buffer.is_file_end)
    {
        puts("file must be ended, but has been enable to read");
        return -1;
    }
    pattern_deinit(&pattern1);
    pattern_deinit(&pattern0);
    if (!dynamic_buffer_deinit(&buffer))
    {
        puts("failed to deinittialize dynamic buffer");
        return -1;
    }
    return 0;
}

const char TOO_LONG_CHARS[0x2000];
int too_many_chars()
{
    puts("Start test 'too_many_chars'");
    FILE *file = fopen("./too_many_chars.txt", "r");
    if (!file)
    {
        puts("can not open file");
        return -1;
    }
    DynamicBuffer buffer;
    // move file owner to buffer
    if (!dynamic_buffer_init(&buffer, file))
    {
        puts("failed to initialize dynamic buffer");
        return -1;
    }
    Pattern pattern;
    if (!dynamic_buffer_get_pattern(&buffer, &pattern))
    {
        puts("can not get pattern");
        return -1;
    }
    printf("%s\n", buffer.buffer);
    if (strncmp(pattern.pattern_str, TOO_LONG_CHARS, pattern.pattern_length) || pattern.pattern_length != 0x2000)
    {
        puts("incorrect pattern");
        return -1;
    }

    if (!buffer.is_file_end)
    {
        puts("file must be ended, but has been enable to read");
        return -1;
    }
    pattern_deinit(&pattern);
    if (!dynamic_buffer_deinit(&buffer))
    {
        puts("failed to deinittialize dynamic buffer");
        return -1;
    }
    return 0;
}

int marks()
{
    puts("Start test 'marks'");
    FILE *file = fopen("./marks.txt", "r");
    if (!file)
    {
        puts("can not open file");
        return -1;
    }
    DynamicBuffer buffer;
    // move file owner to buffer
    if (!dynamic_buffer_init(&buffer, file))
    {
        puts("failed to initialize dynamic buffer");
        return -1;
    }
    char *mark = calloc(2, sizeof(char));
    char *c = mark;
    for ((*c) = '!'; (*c) <= '/'; ++(*c))
    {
        Pattern pattern;
        if (!dynamic_buffer_get_pattern(&buffer, &pattern))
        {
            puts("can not get pattern");
            return -1;
        }
        printf("mark: %s\n", mark);
        printf("pattern: %s\n", pattern.pattern_str);
        printf("pattern_length: %zu\n", pattern.pattern_length);
        if (strncmp(pattern.pattern_str, mark, pattern.pattern_length) || pattern.pattern_length != 1)
        {
            puts("incorrect pattern");
            return -1;
        }
        pattern_deinit(&pattern);
    }

    for ((*c) = ':'; (*c) <= '@'; ++(*c))
    {
        Pattern pattern;
        if (!dynamic_buffer_get_pattern(&buffer, &pattern))
        {
            puts("can not get pattern");
            return -1;
        }
        printf("mark: %s\n", mark);
        printf("pattern: %s\n", pattern.pattern_str);
        printf("pattern_length: %zu\n", pattern.pattern_length);
        if (strncmp(pattern.pattern_str, mark, pattern.pattern_length) || pattern.pattern_length != 1)
        {
            puts("incorrect pattern");
            return -1;
        }
        pattern_deinit(&pattern);
    }

    for ((*c) = '['; (*c) <= '`'; ++(*c))
    {
        Pattern pattern;
        if (!dynamic_buffer_get_pattern(&buffer, &pattern))
        {
            puts("can not get pattern");
            return -1;
        }
        printf("mark: %s\n", mark);
        printf("pattern: %s\n", pattern.pattern_str);
        printf("pattern_length: %zu\n", pattern.pattern_length);
        if (strncmp(pattern.pattern_str, mark, pattern.pattern_length) || pattern.pattern_length != 1)
        {
            puts("incorrect pattern");
            return -1;
        }
        pattern_deinit(&pattern);
    }

    for ((*c) = '{'; (*c) <= '~'; ++(*c))
    {
        Pattern pattern;
        if (!dynamic_buffer_get_pattern(&buffer, &pattern))
        {
            puts("can not get pattern");
            return -1;
        }
        printf("mark: %s\n", mark);
        printf("pattern: %s\n", pattern.pattern_str);
        printf("pattern_length: %zu\n", pattern.pattern_length);
        if (strncmp(pattern.pattern_str, mark, pattern.pattern_length) || pattern.pattern_length != 1)
        {
            puts("incorrect pattern");
            return -1;
        }
        pattern_deinit(&pattern);
    }

    // TODO: ato kara naosu
    /*if (!buffer.is_file_end)
    {
        puts("file must be ended, but has been enable to read");
        return -1;
    }*/
    if (!dynamic_buffer_deinit(&buffer))
    {
        puts("failed to deinittialize dynamic buffer");
        return -1;
    }
    return 0;
}

const char TOO_LONG_CHARS[0x2000] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";