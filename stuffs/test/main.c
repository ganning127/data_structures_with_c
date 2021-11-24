#include "print_ascii_tree.h"

int main()
{
    printf("asdf\n");
    // A sample use of these functions.  Start with the empty tree
    // insert some stuff into it, and then delete it
    NodePtr root;
    int i;
    root = NULL;

    make_empty(root);

    printf("\nAfter inserting key 10..\n");
    root = insert(10, root);
    print_ascii_tree(root);

    printf("\nAfter inserting key 5..\n");
    root = insert(5, root);
    print_ascii_tree(root);

    printf("\nAfter inserting key 15..\n");
    root = insert(15, root);
    print_ascii_tree(root);

    printf("\nAfter inserting keys 9, 13..\n");
    root = insert(9, root);
    root = insert(13, root);
    print_ascii_tree(root);

    printf("\nAfter inserting keys 2, 6, 12, 14, ..\n");
    root = insert(2, root);
    root = insert(6, root);
    root = insert(12, root);
    root = insert(14, root);

    print_ascii_tree(root);

    make_empty(root);
}