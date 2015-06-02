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

sender: $(SRCDIR)/shared.h $(SRCDIR)/sender.h $(SRCDIR)/sender.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/sender.c -o $(OBJDIR)/sender.o

empfaenger: $(SRCDIR)/shared.h $(SRCDIR)/empfaenger.h $(SRCDIR)/empfaenger.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/empfaenger.c -o $(OBJDIR)/empfaenger.o

shared: $(SRCDIR)/shared.h $(SRCDIR)/shared.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/shared.c -o $(OBJDIR)/shared.o

all: sender empfaenger shared
	$(CC) $(OBJDIR)/sender.o $(OBJDIR)/shared.o -o $(BINDIR)/sender -lsem182
	$(CC) $(OBJDIR)/empfaenger.o $(OBJDIR)/shared.o -o $(BINDIR)/empfaenger -lsem182

test:
	sh ./scripts/test_sender_empfaenger.sh -s ./bin/sender -e ./bin/empfaenger

clean:
	rm -f $(OBJDIR)/*.o

cleanresource:
	sh ./scripts/removeResources.sh
