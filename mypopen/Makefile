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

default: mypopen

mypopen: $(SRCDIR)/mypopen.h $(SRCDIR)/mypopen.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/mypopen.c -o $(OBJDIR)/mypopen.o

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
