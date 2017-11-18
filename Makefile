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
all: encode list

encode.o: encode.c list.c list.h
	$(CC) -c encode.c list.c

encode: encode.o list.o list.h
	$(CC) encode.o -o encode 

list.o: list.c list.h
	$(CC) -c list.c

list: list.o list.h
	$(CC) list.o -o list

clean:
	rm -f *.o encode list
