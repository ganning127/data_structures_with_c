#include <stdio.h>
#include <stdlib.h>
void print_in_order(int arr[], size_t length);

int main(void)
{
    int x = 1 + (1 << 10) + (1 << 19) + (1 << 25);
    printf("x: %08x\n", x);
    for (int i = 0; i < 25; i += 8)
    {
        printf("%02d\n", (x << i) >> 24); // 2, 8, 4, 1
        // 02% prints out a whole byte
    }

    int arr[] = {1, 2, 3, 4, 5, 6, 7};

    print_in_order(arr, 7);
    printf("\n");

    // char s[] = "Ganning";
    char c = 'X';
    char *cptr = &c;
    printf("%c\n", *cptr);

    // s is a double pointer: a pointer (*s) to a pointer ("Ganning") to a char ("G")
    char *s[] = {"Ganning", "Dave", "Hello", "World", "Bruh"}; // an array of char pointers
    printf("%c\n", *(s[1]));                                   // D (the address of the first element in a string = address of string)
    s[2] = "Goodbye";
    printf("%s\n", s[1]); // Dave

    puts("");

    char *suits[] = {"Diamonds", "Clubs", "Hearts", "Spades"};
    char *faces[] = {"Deuce", "Crab", "Sailboat", "Nickel", "Boot", "Candy Cane", "Snowman", "Niner", "Dime", "Lancelot", "Sweet Caroline", "Charlemagne", "Seed"};

    int FACES = 13;
    int SUITS = 4;

    for (size_t i = 0; i < FACES * SUITS; ++i)
    {
        printf("Suit: %s - Face: %s\n", suits[i / FACES], faces[i % FACES]);
    }

    return 0;
}

void print_in_order(int arr[], size_t length)
{
    // printf("len: %d\n", length);
    if (length == 0)
    {
        printf("\n");
        return;
    }
    print_in_order(arr, length - 1);
    printf("%d ", arr[length - 1]);
}