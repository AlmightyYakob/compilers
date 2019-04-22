CC=gcc
CFLAGS=-S -fno-asynchronous-unwind-tables
OPTFLAGS=-m32

all: any

any:
	$(CC) $(OPTFLAGS) *.c $(CFLAGS)

assemble: main.s
	$(CC) $(OPTFLAGS) main.s -o main

main.s: main.c
	$(CC) $(OPTFLAGS) main.c $(CFLAGS)

clean:
	rm -f main *.o *.out *.s
