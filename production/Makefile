CC=gcc

CFLAGS=-g -Wall -I. -I ./include
LDFLAGS=-g -L/usr/local/lib -lwiringPi -lyaml

all: garment

garment : garment.o global_variables.o libsetup_led.o 
	$(CC) -o garment garment.o libsetup_led.o global_variables.o $(LDFLAGS)

global_variables.o: global_variables.cpp include/lighted.h
	$(CC) -c $(CFLAGS) global_variables.cpp

libsetup_led.o: libsetup_led.cpp include/lighted.h
	$(CC) -c $(CFLAGS) libsetup_led.cpp

garment.o: garment.cpp include/lighted.h
	$(CC) -c $(CFLAGS) garment.cpp

objects := global_variables.o libsetup_led.o garment.o

targets := garment

clean:
	rm -f $(objects) $(targets)

.PHONY: default clean
