#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 1
#define LOAD_FACTOR_MIN 4
#define LOAD_FACTOR_MAX 5

typedef struct hash_node
{
    char *key;
    int value;
    struct hash_node *next;
} HNode;

typedef struct arraylist_nodes
{
    HNode **array;
    size_t keys;
    size_t capacity;
} ArrayListNodes;

void resize(ArrayListNodes *, size_t new_capcity);
ArrayListNodes *arln_create();
size_t hash(char *str, size_t size);
void arln_destroy(ArrayListNodes **listPtr);
void arln_insert(ArrayListNodes *list, char *key, int value);
int arln_get(ArrayListNodes *list, char *key);
void alrn_delete(ArrayListNodes *list, char *key);

int main(void)
{
    ArrayListNodes *nList = arln_create();
    arln_insert(nList, "a", 3);
    arln_insert(nList, "b", 4);
    arln_insert(nList, "c", 5);
    arln_insert(nList, "d", 6);
    arln_insert(nList, "e", 7);
    arln_insert(nList, "f", 8);
    arln_insert(nList, "g", 9);
    arln_insert(nList, "h", 10);
    arln_insert(nList, "i", 11);
    arln_insert(nList, "j", 12);

    arln_destroy(&nList);
    free(nList);
    return 0;
}

void resize(ArrayListNodes *list, size_t new_capacity)
{
    HNode **new_array = (HNode **)malloc(sizeof(HNode *) * new_capacity);

    for (size_t i = 0; i < new_capacity; i++)
    {
        new_array[i] = NULL; // go through each node and set it to NULL
    }

    for (size_t i = 0; i < list->capacity; i++)
    {
        HNode *curr = list->array[i]; // get the current node
        while (curr != NULL)
        {
            size_t index = hash(curr->key, new_capacity); // get the index of the node in the new array
            HNode *next = curr->next;
            curr->next = new_array[index];
            new_array[index] = curr;
            curr = next;
        }
    }
    free(list->array); // free memory of old array
    list->array = new_array;
    list->capacity = new_capacity;
}

int arln_get(ArrayListNodes *list, char *key)
{
    size_t index = hash(key, list->capacity);
    HNode *node = list->array[index];
    int key_found = 0;

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            return node->value;
        }
        node = node->next;
    }
    printf("key: %s was not found, returning -1.\n", key);
    return -1;
}

HNode *find_node(HNode *node, char *key)
{
    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void arln_insert(ArrayListNodes *list, char *key, int value)
{
    size_t index = hash(key, list->capacity);
    HNode *nu = malloc(sizeof(HNode));
    nu->key = key;
    nu->value = value;
    nu->next = NULL;

    if (list->array[index] == NULL)
    {
        list->array[index] = nu;
    }
    else
    {
        // TODO: check if the key is already in there
        /*
            if the key is already there, move it to the front of the linked list
        */

        HNode *curr = list->array[index];
        HNode *node_found = find_node(curr, key);

        if (node_found)
        {
            // move the node to the beginning of linked list
        }
        HNode *current = list->array[index];
        list->array[index] = nu; // insert to beg of linked list
        nu->next = current;
    }

    list->keys++;

    if (list->keys > list->capacity * LOAD_FACTOR_MAX) // change this
        resize(list, list->capacity * 2);
}

void alrn_delete(ArrayListNodes *list, char *key)
{
    size_t index = hash(key, list->capacity);
    HNode *curr = list->array[index];
    HNode *prev = NULL;

    while (curr != NULL)
    {
        if (strcmp(curr->key, key) == 0)
        {
            if (prev == NULL)
            {
                list->array[index] = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            list->keys--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    if (list->keys < list->capacity * LOAD_FACTOR_MIN)
        resize(list, list->capacity / 2);
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

ArrayListNodes *arln_create()
{
    ArrayListNodes *list = malloc(sizeof(ArrayListNodes));
    list->keys = 0;
    list->capacity = INITIAL_SIZE;
    list->array = calloc(sizeof(HNode *), INITIAL_SIZE);
    // set all the pointers to NULL
    for (size_t i = 0; i < list->capacity; i++)
    {
        list->array[i] = NULL;
    }
    return list;
}

void lldestroy(HNode **list)
{
    // delete nodes in the linked list
    HNode *node = *list;
    if (node != NULL)
    {
        // destroy the rest of the list
        lldestroy(&(node->next));
        free(node);   // free the memory created in malloc
        *list = NULL; // empty list
    }
}

void arln_destroy(ArrayListNodes **listPtr)
{
    ArrayListNodes *list = *listPtr;
    for (size_t i = 0; i < list->capacity; ++i)
    {
        lldestroy(&(list->array[i]));
        free(list->array[i]);
    }
    free(list->array);
    free(list);
    *listPtr = NULL;
}

/*
    Struct Node {
        String string;
        node *next;
    }

    Hashing: process of turning a key into a hash keys.
        - a collision occurs when two keys have the same hash keys
        - this makes two things map to the same hash value

    HashFunction():
        hash = 0;
        for each char in string:
            hash = (hash * 31 + char) %M // M is the array size // 31 because that is what java uses
        return hash

    if there are two different keys with the same hash value, then there is a collision
    CollisionResolution():
        - array of linked lists
        - each linked list is a bucket

    Reize HashMap:
        - double the size of the array
        - rehash all the keys in the old array into the new array
        - update the hash function to use the new array size

    LoadFactor
        - we do NOT want to wait until hash_map is full to resize it
        - we want to resize it when the load factor is greater than 2/3 or 0.6666667
        - loadFactor = nodes / arraySize

*/

/*
Open addressing:
LOAD FACTORS:
    < 0.6: half the size
    >= 0.7: double the size

insert():
    - go to index of the hash, and check if it is full
    - if it is full, keep going to find a new index
        - linear probing (go to next index) (WE ARE NOT GOING TO DO THIS)
    - if the index in which you want to insert is already marked by an alemenet ready for deletion,
        - replace that node with the thing you want to delete

delete():
    - hash the key that you want to delete
    - go to the index of the hash
    - check if the key is there
    - if it is there, mark it ready for deletion
*/