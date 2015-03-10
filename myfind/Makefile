CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wstrict-prototypes -pedantic -fno-common -g -O3
SRCDIR = src
OBJDIR = obj
BINDIR = bin

default: all

main: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o

parseopt: $(SRCDIR)/parseopt.h $(SRCDIR)/parseopt.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/parseopt.c -o $(OBJDIR)/parseopt.o

printers: $(SRCDIR)/printers.h $(SRCDIR)/printers.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/printers.c -o $(OBJDIR)/printers.o

all: main parseopt printers
	$(CC) $(OBJDIR)/main.o $(OBJDIR)/parseopt.o $(OBJDIR)/printers.o -o $(BINDIR)/myfind

valgrind:
	valgrind --leak-check=full ./bin/myfind . -nouser -name test

valgrind-verbose:
	valgrind --leak-check=full -v ./bin/myfind . -nouser -name test

clean:
	rm -f $(OBJDIR)/*.o
