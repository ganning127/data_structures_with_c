#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define INITIAL_SIZE 1
#define LOAD_FACTOR_MAX 0.7
#define LOAD_FACTOR_MIN 0.25

typedef struct hash_node
{
    char *key;
    int value;
    bool to_be_deleted;
} HNode;
typedef HNode *HNodePtr;

typedef struct arraylist_nodes
{
    HNode *array;
    size_t size;
    size_t capacity;
} ArrayListNodes;

void insert(ArrayListNodes *list, char *key, int value);
void delete (ArrayListNodes *list, char *key);
int get(ArrayListNodes *list, char *key);
size_t find(ArrayListNodes *list, char *key);
size_t hash(char *str, size_t size);
void resize(ArrayListNodes *list, size_t new_capacity);
void showAllBuckets(ArrayListNodes *list);
ArrayListNodes *arln_create();
void arln_destroy(ArrayListNodes *list);
double getLoadFactor(ArrayListNodes *list);

int main(void)
{
    // if you try to get a key that has been marked for deletion, the function will return 0
    ArrayListNodes *list = arln_create();
    insert(list, "key1", 1);
    insert(list, "key2", 2);
    insert(list, "key3", 3);
    insert(list, "key4", 4);
    insert(list, "key5", 5);
    insert(list, "key6", 6);

    delete (list, "key3");
    delete (list, "key4");
    delete (list, "ganning"); // should say not found

    printf("%s : %d\n", "key1", get(list, "key1"));
    printf("%s : %d\n", "key2", get(list, "key2"));
    printf("%s : %d\n", "key3", get(list, "key3")); // should say not found, since it was deleted, returns 0
    printf("%s : %d\n", "key4", get(list, "key4")); // should say not found, since it was deleted, returns 0
    printf("%s : %d\n", "haha", get(list, "haha")); // should say not found, returns 0
    printf("%s : %d\n", "key5", get(list, "key5"));

    arln_destroy(list);
    return 0;
}

ArrayListNodes *arln_create()
{
    ArrayListNodes *list = malloc(sizeof(ArrayListNodes));
    list->size = 0;
    list->capacity = INITIAL_SIZE;
    list->array = calloc(sizeof(HNode), INITIAL_SIZE);
    return list;
}

void arln_destroy(ArrayListNodes *list)
{
    free(list->array);
    free(list);
}

void showAllBuckets(ArrayListNodes *list)
{
    for (size_t i = 0; i < list->capacity; i++)
    {
        printf("Bucket %zu = ", i);
        if (list->array[i].key)
        {
            if (list->array[i].to_be_deleted)
            {
                printf("%s: %d (marked for del)\n", list->array[i].key, list->array[i].value);
            }
            else
            {
                printf("%s: %d\n", list->array[i].key, list->array[i].value);
            }
        }
        else
            printf("\n");
    }
}

size_t find_empty_index(HNode *list, size_t capacity, size_t orig_hash)
{
    // printf("list capacity: %zu\n", list->capacity);
    size_t i = 0;
    size_t index = orig_hash;
    while (list[index].key != NULL)
    {
        if (list[index].to_be_deleted)
            return index;

        index = (orig_hash + (i + (i * i)) / 2) % capacity;
        // the spot to insert can either be empty or marked for deletion
        i++;
    }

    return index; // list->array[index] must be NULL
}

void insert(ArrayListNodes *list, char *key, int value)
{
    size_t found_index = find(list, key); // check if the node is already in the list
    if (found_index != list->capacity)
    {
        // if the key is already in the list, just update the value
        list->array[found_index].value = value;
        list->array[found_index].to_be_deleted = false;
        return;
    }

    // if the key is not already in the list, then we need to insert it
    size_t hash_value = hash(key, list->capacity);
    size_t index = find_empty_index(list->array, list->capacity, hash_value);
    // printf("index: %zu\n", index);
    list->array[index].key = key;
    list->array[index].value = value;
    list->array[index].to_be_deleted = false;
    list->size++;

    if (getLoadFactor(list) > LOAD_FACTOR_MAX)
    {
        resize(list, list->capacity * 2);
    }
}

void delete (ArrayListNodes *list, char *key)
{
    size_t hash_value = hash(key, list->capacity);
    size_t index = find(list, key);
    if (index == list->capacity)
    {
        printf("key \"%s\" not found and cannot be deleted.\n", key);
        return;
    }

    list->array[index].to_be_deleted = true;
    list->size--; // means that we don't include deleted nodes in the size
    if (getLoadFactor(list) < LOAD_FACTOR_MIN)
    {
        resize(list, list->capacity / 2);
    }
}

int get(ArrayListNodes *list, char *key)
{
    size_t hash_value = hash(key, list->capacity);
    size_t index = find(list, key);
    if (index == list->capacity || list->array[index].to_be_deleted)
    {
        printf("key \"%s\" not found, or was already deleted.\n", key);
        return 0;
    }
    return list->array[index].value;
}

void resize(ArrayListNodes *list, size_t new_capacity)
{
    HNode *new_array = calloc(sizeof(HNode), new_capacity);
    for (size_t i = 0; i < list->capacity; i++)
    {
        if (list->array[i].key != NULL && !list->array[i].to_be_deleted)
        {
            size_t hash_value = hash(list->array[i].key, new_capacity);
            size_t index = find_empty_index(new_array, new_capacity, hash_value);
            new_array[index] = list->array[i];
        }
    }
    free(list->array);
    list->array = new_array;
    list->capacity = new_capacity;
}

size_t find(ArrayListNodes *list, char *key)
{
    // need this thing to return list -> capacity when key is not found
    size_t hash_value = hash(key, list->capacity);
    size_t i = 0;
    size_t index = hash_value;

    while (list->array[index].key != NULL)
    {
        if (strcmp(list->array[index].key, key) == 0)
            return index;
        index = (hash_value + (i + (i * i)) / 2) % list->capacity;
        ++i;
    }
    return list->capacity; // if the key is not found, return the capacity
}

size_t hash(char *str, size_t size)
{
    // generate a hash value for a string (to index into array)
    size_t hash = 0;
    while (*str != '\0')
    {
        hash = (hash * 31 + *str) % size;
        ++str;
    }

    return hash;
}

double getLoadFactor(ArrayListNodes *list)
{
    return (double)list->size / list->capacity;
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
