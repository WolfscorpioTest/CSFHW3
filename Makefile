CC=g++
CFLAGS=-Wall -Wextra -pedantic -g

.PHONY: all
all: csim

csim: main.cpp
	$(CC) $(CFLAGS) main.cpp -o csim


assign3.zip:
	zip assign3.zip *.cpp *.h README.txt

clean:
	rm *.o csim assign3.zip

