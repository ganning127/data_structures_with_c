#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 8

typedef struct hash_node
{
    char *key;
    int value;
} HNode;
typedef HNode *HNodePtr;

typedef struct arraylist_strings
{
    char **array;    // declared as pointer so we don't need to specify size
    size_t size;     // how many elements its currently holding
    size_t capacity; // how many elements it can hold
} ArrayListStrings;

typedef struct arraylist_nodes
{
    HNode **array;
    size_t size;
    size_t capacity;
} ArrayListNodes;

size_t find(ArrayListNodes *list, char *key);
size_t hash(char *str, size_t size);

ArrayListNodes *arln_create();

int main(void)
{
    // find function is below

    return 0;
}

size_t find(ArrayListNodes *list, char *key)
{
    // need this thing to return list -> capacity when key is not found
    size_t hash_value = hash(key, list->capacity);
    size_t index = hash_value;

    while (list->array[index] != NULL)
    {
        if (strcmp(list->array[index]->key, key) == 0)
        {
            return index;
        }
        index = (size_t)(hash_value + (0.5 * index) + (0.5 * index * index)) % list->capacity;
    }
    return list->capacity;
}

size_t hash(char *str, size_t size)
{
    // generate a hash value for a string (to index into array)
    size_t hash = 0;
    while (*str != '\0')
    {
        // printf("%c", *str);
        hash = (hash * 31 + *str) % size;
        ++str;
    }

    return hash;
}