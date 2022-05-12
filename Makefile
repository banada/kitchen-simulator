CC=gcc
CFLAGS= -g -Wall

LIBDIR=$(PWD)/lib
LIBKITCHENSINK=libkitchensink

BINDIR=$(PWD)/bin


all: setup omelette

setup:
	mkdir -p $(LIBDIR)/$(LIBKITCHENSINK)
	mkdir -p $(BINDIR)

omelette: libkitchensink
	$(CC) $(CFLAGS) -o $(BINDIR)/omelette omelette.c -L$(LIBDIR)/$(LIBKITCHENSINK) -lkitchensink

libkitchensink:
	$(CC) -o $(LIBDIR)/$(LIBKITCHENSINK)/pan.o -c pan.c
	$(CC) -o $(LIBDIR)/$(LIBKITCHENSINK)/stove.o -c stove.c
	ar -cvq $(LIBDIR)/$(LIBKITCHENSINK)/libkitchensink.a $(LIBDIR)/$(LIBKITCHENSINK)/pan.o $(LIBDIR)/$(LIBKITCHENSINK)/stove.o

clean:
	rm -rf $(LIBDIR)
	rm -rf $(BINDIR)
