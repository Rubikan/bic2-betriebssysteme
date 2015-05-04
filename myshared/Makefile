CC 			= gcc
CFLAGS  = -Wall -Werror -Wextra -Wstrict-prototypes -pedantic -fno-common -g -O3
DOXYGEN = doxygen
SRCDIR  = src
OBJDIR  = obj
BINDIR  = bin
CP			= cp
CD			= cd
MV			= mv
GREP		= grep

default: all

sender: $(SRCDIR)/sender.h $(SRCDIR)/sender.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/sender.c -o $(OBJDIR)/sender.o

empfaenger: $(SRCDIR)/empfaenger.h $(SRCDIR)/empfaenger.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/empfaenger.c -o $(OBJDIR)/empfaenger.o

all: sender empfaenger
	$(CC) $(OBJDIR)/sender.o -o $(BINDIR)/sender
	$(CC) $(OBJDIR)/empfaenger.o -o $(BINDIR)/empfaenger

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
