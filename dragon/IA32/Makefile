CC=gcc
CFLAGS=-S -fno-asynchronous-unwind-tables
OPTFLAGS=-m32

any:
	$(CC) $(OPTFLAGS) *.c $(CFLAGS)

all: main

main: main.c
	$(CC) $(OPTFLAGS) main.c $(CFLAGS)

clean:
	rm -f *.s
