CC=g++
CFLAGS=-Wall -Wextra -pedantic -g

.PHONY: all
all: csim

csim: main.cpp Cache.h
	$(CC) $(CFLAGS) main.cpp -o csim


assign3.zip:
	zip assign3.zip *.cpp *.h Makefile README.txt

clean:
	rm -f *.o csim assign3.zip

