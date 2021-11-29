#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
        index = (size_t)(hash_value + (0.5 * index) + (0.5 * index * index)) % list->capacity; // look at the next index
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

/*
Open addressing: ArrayList of HNodes (not pointers)

LOAD FACTORS:
    < 0.25 : half the size
    >= 0.7: double the size
    - don't include deleted items in load factor because they will be removed anyways

struct node {
    char *key;
    int value;
    bool marked_for_deletion;
};

insert():
    - go to index of the hash, and check if it is full
    - if it is full, keep going to find a new index
        - linear probing (go to next index) (WE ARE NOT GOING TO DO THIS)
    - if the index in which you want to insert is already marked by an alemenet ready for deletion,
        - replace that node with the thing you want to delete
    - check if exceeding load factor upper
        if so, resize

delete():
    - hash the key that you want to delete
    - go to the index of the hash
    - check if the key is there
    - if it is there, mark it ready for deletion
    - don't remove the node until we resize the hashmap
    - check if exceeding load factor lower
        if so, resize



*/