CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
SRCDIR = src
OBJDIR = obj
BINDIR = bin

default: all

main: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o

all: main
	$(CC) $(OBJDIR)/main.o -o $(BINDIR)/myfind 

clean: 
	rm -f $(OBJDIR)/*.o 