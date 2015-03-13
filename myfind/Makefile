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

html:
	$(DOXYGEN) doxygen.dcf

pdf: html
	$(CD) doc/pdf && \
	$(MV) refman.tex refman_save.tex && \
	$(GREP) -v $(EXCLUDE_PATTERN) refman_save.tex > refman.tex && \
	$(RM) refman_save.tex && \
	make && \
	$(MV) refman.pdf refman.save && \
	$(RM) *.pdf *.html *.tex *.aux *.sty *.log *.eps *.out *.ind *.idx \
	      *.ilg *.toc *.tps Makefile && \
	$(MV) refman.save refman.pdf

doc: html pdf

clean:
	rm -f $(OBJDIR)/*.o

clean-doc:
	rm -rf doc
