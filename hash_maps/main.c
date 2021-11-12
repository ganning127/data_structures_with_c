#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
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
        - loadFactor = numElements / arraySize

*/