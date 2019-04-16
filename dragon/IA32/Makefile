CC=gcc
CFLAGS=-S -fno-asynchronous-unwind-tables
OPTFLAGS=-m32

all: main


main: main.c
	$(CC) main.c $(CFLAGS)

clean:
	rm -f main.s
