CC=gcc
CFLAGS=-S -fno-asynchronous-unwind-tables
OPTFLAGS=-m32

any:
	$(CC) *.c $(CFLAGS) $(OPTFLAGS)

all: main

main: main.c
	$(CC) main.c $(CFLAGS) $(OPTFLAGS)

clean:
	rm -f *.s
