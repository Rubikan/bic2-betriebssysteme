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

checks: $(SRCDIR)/checks.h $(SRCDIR)/checks.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/checks.c -o $(OBJDIR)/checks.o

all: main parseopt checks
	$(CC) $(OBJDIR)/main.o $(OBJDIR)/parseopt.o $(OBJDIR)/checks.o -o $(BINDIR)/myfind

test: all
	/usr/local/bin/test-find.sh -t ./bin/myfind -r /usr/local/bin/bic-myfind -c

test-full: all
	/usr/local/bin/test-find.sh -t ./bin/myfind -r /usr/local/bin/bic-myfind -c -f

valgrind:
	valgrind --leak-check=full ./bin/myfind . -nouser -name test

valgrind-verbose:
	valgrind --leak-check=full -v ./bin/myfind . -nouser -name test

clean:
	rm -f $(OBJDIR)/*.o
