CC = gcc
CFLAGS  = -Wall -Werror -Wextra -Wstrict-prototypes -pedantic -fno-common -g -O3
DOXYGEN = doxygen
SRCDIR  = src
OBJDIR  = obj
BINDIR  = bin
CP			= cp
CD			= cd
MV			= mv
GREP		= grep

default: test

mypopen: $(SRCDIR)/mypopen.h $(SRCDIR)/mypopen.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/mypopen.c -o $(OBJDIR)/mypopen.o

build-test: mypopen
	$(CC) $(CFLAGS) $(OBJDIR)/mypopen.o -lpopentest -o $(BINDIR)/popentest

test: build-test
	./bin/popentest

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
