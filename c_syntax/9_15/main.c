#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    char *first_name;
    char *last_name;
    int number[10];
    unsigned long age;
    char gender;
    void (*function)(int);

    struct student *friend; // student.friend is a pointer
} Student;                  // student.first_name

typedef struct test
{
    int a;
    char b;
} Test;

union number
{
    int x;
    double y;
    union number *vPtr;

}; // can only have one of those two things

// every element in the struct is given enough memory as the largest element in the struct

void fun1(int x);
int arithmetic(int a, int b, int (*op)(int, int));

int add(int a, int b);
int subtract(int a, int b);

int main(void)
{
    void (*fun_ptr)(int) = &fun1; // needs: return type, arg type, and assign to memory address of fun1

    (*fun_ptr)(6); // call the function by dereferencing pointer
    printf("%d\n", arithmetic(10, 6, &add));

    int (*fun_ptr_arr[])(int, int) = {&add, &subtract};
    // int = integer return type of each function
    // *fun_ptr_arr[] = array of function pointers
    // (int, int) = each of the functions have 2 args of `int`

    for (size_t i = 0; i < 2; ++i)
    {
        printf("%d\n", fun_ptr_arr[i](42, 6));
    }

    // STRUCT

    Student me =
        {
            "Ganning",
            "Xu",
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            16,
            'M'};

    for (size_t i = 0; i < 10; ++i)
    {
        printf("%d\n", me.number[i]);
    }
    me.last_name = "new_last_name";
    puts(me.last_name);
    me.function = &fun1;

    (*me.function)(12);

    printf("struct addr: %p\n", &me);
    printf("first_name addr: %p\n", &me.first_name);
    printf("last_name addr: %p\n", &me.last_name);
    printf("number addr: %p\n", &me.number);
    printf("age addr: %p\n", &me.age);
    printf("gender addr: %p\n", &me.gender); // 8 bytes wide
    printf("function addr: %p\n", &me.function);

    printf("sizeof me: %zu\n", sizeof(me));

    Test test1 = {1, 'a'};
    printf("a addr: %p\n", &test1.a);
    printf("b addr: %p\n", &test1.b);
    printf("sizeof test1: %zu\n", sizeof(test1));

    me.friend = &me;

    puts((*me.friend).first_name);
    puts(me.friend->first_name); // -> accesses attributes of a struct pointer

    union number value;
    value.x = 100;
    printf("%d, %f\n", value.x, value.y);

    value.y = 1200;
    printf("%d, %f\n", value.x, value.y);

    printf("%zu\n", sizeof(union number));

    union number *vPtr = &value; // breaks code
    vPtr->x = 42;                // breaks code
    printf("%d, %f\n", value.x, value.y);

    typedef struct student
    {
        char *first_name;
        char last_name[2];
    } Student;

    Student me = {
        "Ganning",
        "Xu"};

    printf("&me: %p\n", &me);
    printf("&me.first_name: %p\n", &(me.first_name));
    printf("&me.last_name[0]: %p\n", &(me.last_name[0]));
    printf("&me.last_name[1]: %p\n", &(me.last_name[1]));

    printf("length: %lu\n", sizeof(me));

    return 0;
}

void fun1(int x)
{
    printf("x: %d\n", x);
}

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int arithmetic(int a, int b, int (*op)(int, int))
{
    // takes in a function `op()` as argument
    return (*op)(a, b); // `parent` function
}