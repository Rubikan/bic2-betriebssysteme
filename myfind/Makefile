CC = gcc
CFLAGS_BETTER = -Wall -Werror -Wextra -pedantic -g
CFLAGS = -Wall
SRCDIR = src
OBJDIR = obj
BINDIR = bin

default: all

main: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o

parseopt: $(SRCDIR)/parseopt.h $(SRCDIR)/parseopt.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/parseopt.c -o $(OBJDIR)/parseopt.o

link:
	$(CC) $(OBJDIR)/main.o $(OBJDIR)/parseopt.o -o $(BINDIR)/myfind

all: main parseopt
	$(CC) $(OBJDIR)/main.o $(OBJDIR)/parseopt.o -o $(BINDIR)/myfind

clean:
	rm -f $(OBJDIR)/*.o
