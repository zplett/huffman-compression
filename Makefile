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
all: encode

list.o: encode.c encode.h
	$(CC) -c encode.c

list: encode.o encode.h
	$(CC) encode.o -o encode

clean:
	rm -f *.o encode 
