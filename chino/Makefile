CC=gcc
CFLAGS=-std=c99 -Wall
all:main.o immcode.h
	$(CC) $(CFLAGS) main.o -o chino
main.o:main.cpp immcode.h
	$(CC) -c $(CFLAGS) main.cpp
install:chino
	cp chino /usr/local/bin/chino
uninstall:
	rm /usr/local/bin/chino
