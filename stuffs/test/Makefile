program_NAME := main.out

SRCS = main.c 
OBJS := ${SRCS:.c=.o}
CFLAGS = -fsanitize=address -c

program_INCLUDE_DIRS := .
program_LIBRARY_DIRS := .
program_LIBRARIES := .

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

LINK.c := $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

.PHONY: all

all: $(program_NAME)

$(program_NAME): $(OBJS) 
	$(LINK.c) $(program_OBJS) -o $(program_NAME) 

clean:
	rm -rf *.o *.out