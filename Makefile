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

encode.o: encode.c list.c list.h
	$(CC) -c list.c encode.c

encode: list.o encode.o list.h
	$(CC) encode.o -o encode 

clean:
	rm -f *.o encode
