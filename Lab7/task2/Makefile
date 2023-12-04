CC = gcc
CFLAGS = -Wall

all: client server

client: childsProgram.c
	$(CC) $(CFLAGS) -o childsProgram childsProgram.c

server: main.c
	$(CC) $(CFLAGS) -o main main.c

clean:
	rm -f client server
