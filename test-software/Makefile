CC=gcc

CFLAGS=-g -Wall -Wextra pkg-config libxml++-2.6 -I. -I ./include
LDFLAGS=-g -L/usr/local/lib -lwiringPi

all: test_program

test_program: test_program.o
	$(CC) -o test_program test_program.cpp $(LDFLAGS)
test_program.o: test_program.cpp
	$(CC) -c $(CFLAGS) test_program.cpp

objects := test_program.o
targets := test_program

clean:
	rm -f $(objects) $(targets)

.PHONY: default clean
