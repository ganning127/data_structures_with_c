OBJS := ${SRCS:.c=.o}
libprint_ascii_tree.a: print_ascii_tree.o
	ar -rcs libprint_ascii_tree.a print_ascii_tree.o

print_ascii_tree.o: print_ascii_tree.c 
	gcc -c print_ascii_tree.c -o print_ascii_tree.o


clean:
	rm -rf *.o *.a