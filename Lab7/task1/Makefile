CC = gcc
CFLAGS = -Wall

all: program1 program2

program1: main.c
	$(CC) $(CFLAGS) -o main main.c

program2: childsProgram.c
	$(CC) $(CFLAGS) -o childsProgram childsProgram.c

clean:
	rm -f program1 program2
