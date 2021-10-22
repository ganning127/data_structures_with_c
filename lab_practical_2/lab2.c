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

char **p1(size_t size);
char **p2(char **strings, size_t size);
char **p3(char **strings, size_t size);
char *p4(char *stringPtr, char *string[], size_t size);
char *p5(NamePtr name);

int main(void)
{
    char **p1_res = p1(3);
    char **p2_res = p2(p1_res, 3);

    char *strings[] = {"Ganning", "Bob", "Xu"};
    char **p3_res = p3(strings, 3);
    printf("p3_res: ");
    for (size_t i = 0; i < 3; ++i)
        printf("%s ", p3_res[i]);

    puts("");
    puts("");

    char *stringPtr = malloc(sizeof(char *));
    char *strings1[] = {"string1", "string2", "string3", "string4"};
    char *p4_res = p4(stringPtr, strings1, 4);
    printf("p4_res: %s\n", p4_res);

    puts("");

    NamePtr name = malloc(sizeof(Name));
    name->first = "Ganning";
    name->middle = "";
    name->last = "Xu";
    char *p5_res = p5(name);
    printf("p5_res: %s\n", p5_res);

    free(p5_res);
    free(name);
    free(stringPtr);
    return 0;
}

char **p1(size_t size)
{
    // DONE
    return calloc(size, sizeof(char *));
}

char **p2(char **strings, size_t size)
{
    // DONE
    return realloc(*strings, size * 2);
}

char **p3(char **strings, size_t size)
{
    // DONE
    char **duplicate = malloc(sizeof(strings) * size);
    for (size_t i = 0; i < size; ++i)
    {
        duplicate[i] = malloc(sizeof(strings[i]));
        strcpy(duplicate[i], strings[i]);
    }

    puts("");
    return duplicate;
}
char *p4(char *stringPtr, char *strings[], size_t size)
{
    // DONE
    for (size_t i = 0; i < size; ++i)
        strcat(stringPtr, strings[i]);
    return stringPtr;
}

char *p5(NamePtr name)
{
    // DONE
    char *full_name = malloc(sizeof(name->first) * 3);
    if (name->first != NULL && strcmp(name->first, ""))
        strcat(full_name, name->first);
    if (name->middle != NULL && strcmp(name->middle, ""))
    {
        strcat(full_name, " ");
        strcat(full_name, name->middle);
    }
    if (name->last != NULL && strcmp(name->last, ""))
    {
        strcat(full_name, " ");
        strcat(full_name, name->last);
    }

    return full_name;
}
