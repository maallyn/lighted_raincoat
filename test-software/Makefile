CC=gcc

CFLAGS=-g -I. -I ./include
LDFLAGS=-g -L/usr/local/lib -lwiringPi

all: test_program

test_program: test_program.o
	$(CC) -o test_program test_program.c $(LDFLAGS)
test_program.o: test_program.c
	$(CC) -c $(CFLAGS) test_program.c

objects := test_program.o
targets := test_program

clean:
	rm -f $(objects) $(targets)

.PHONY: default clean
