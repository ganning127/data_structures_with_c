program_NAME := main.out

SRCS = main.c 
OBJS := ${SRCS:.c=.o}
CFLAGS = -fsanitize=address -Wall -Wextra -g

program_INCLUDE_DIRS := ../include
program_LIBRARY_DIRS := ../print_ascii_tree
program_LIBRARIES := print_ascii_tree

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

LINK.c := $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

.PHONY: all

all: $(program_NAME)

$(program_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -rf *.o *.out