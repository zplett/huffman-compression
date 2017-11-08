# Detect OS for clfags, indicates when gccx can be used
OS := $(shell uname)

# Establish OS specific commands
ifeq ($(OS), Darwin)
	CC := gcc -g -pedantic -std=c99 -Wall -Wextra
else
	ifeq ($(OS), Linux)
		CC := gccx
	endif
endif
# End of OS specification

# Compilation specification
all: list

list.o: list.c
	$(CC) -c list.c

list: list.o
	$(CC) list.o -o list

clean:
	rm -f *.o list 
