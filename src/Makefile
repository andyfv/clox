# -*- Makefile -*-

# target: dependencies
# 	action
CC 	= gcc
OBJ = main.o chunk.o debug.o memory.o value.o vm.o

all: clox clean

clox: $(OBJ)
	$(CC) -o $@ $^

%*.o: %.c
	$(CC) -c $@

clean: 
	rm *.o clox