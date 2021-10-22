#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct name
{
    char *first;
    char *middle;
    char *last;
} Name;

typedef Name *NamePtr;

char **p1(size_t size)
{
    // DONE
    return calloc(size, sizeof(char *));
}

char **p2(char **strings, size_t size)
{
    // DONE
    return realloc(strings, size * 2 * sizeof(char *));
}

char **p3(char **strings, size_t size)
{
    // DONE
    // char **duplicate = malloc(sizeof(strings) * size);
    char **duplicate = malloc(size * sizeof(char *));
    for (size_t i = 0; i < size; ++i)
    {
        if (strings[i])
        {
            duplicate[i] = calloc(strlen(duplicate[i] + 1), sizeof(char));
            strcpy(duplicate[i], strings[i]);
        }
    }

    puts("");
    return duplicate;
}

char *p4(char **stringPtr, char *strings[], size_t size)
{
    size_t length = strlen(*stringPtr) + 1;
    for (size_t i = 0; i < size; ++i)
        length += strlen(strings[i]);

    char *out = calloc(length, sizeof(char));
    strcat(out, *stringPtr); // `out` has a null character at the beginning
    for (size_t i = 0; i < size; ++i)
        strcat(out, strings[i]);
    *stringPtr = out;
}

char *p5(NamePtr name)
{
    size_t length = 1;

    if (name->first)
    {
        length += strlen(name->first);
        if (name->middle || name->last)
            length += 1;
    }
    if (name->middle)
    {
        length += strlen(name->middle);
        if (name->last)
            length += 1;
    }
    if (name->last)
        length += strlen(name->last);

    char *out = calloc(length, sizeof(char));
    if (name->first)
    {
        strcat(out, name->first); // null character comes immedielty
        if (name->middle)
        {
            strcat(out, " ");
        }
    }
    if (name->middle)
    {
        strcat(out, name->middle);
        if (name->last)
        {
            strcat(out, " ");
        }
    }
    if (name->last)
        strcat(out, name->last);
    return out;
}

int main(void)
{
    char **p1_res = p1(10);

    for (size_t i = 0; i < 10; ++i)
        printf("%s ", p1_res[0]);

    puts("");

    NamePtr name = malloc(sizeof(Name));

    name->first = "Ganning";
    name->middle = "Middle";
    name->last = "Xu";
    printf("%s\n", p5(name));

    return 0;
}
