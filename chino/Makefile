CC=gcc
CFLAGS=-std=c99 -Wall
chino:main.o immcode.h
	$(CC) $(DBGF) main.o -o chino $(CFLAGS)
main.o:main.cpp immcode.h
	$(CC) -c $(DBGF) main.cpp $(CFLAGS)
install:chino
	cp chino /usr/local/bin
uninstall:
	rm /usr/local/bin
