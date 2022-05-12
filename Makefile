CC=gcc
CFLAGS= -g -Wall

LIBDIR=$(PWD)/lib
LIBKITCHENSINK=libkitchensink

BINDIR=$(PWD)/bin


all: setup omelette stove

setup:
	mkdir -p $(LIBDIR)/$(LIBKITCHENSINK)
	mkdir -p $(BINDIR)

omelette: libkitchensink
	$(CC) $(CFLAGS) -o $(BINDIR)/omelette omelette.c -L$(LIBDIR)/$(LIBKITCHENSINK) -lkitchensink

libkitchensink:
	$(CC) -o $(LIBDIR)/$(LIBKITCHENSINK)/pan.o -c pan.c
	$(CC) -o $(LIBDIR)/$(LIBKITCHENSINK)/stove.o -c stoved/stove.c
	ar -cvq $(LIBDIR)/$(LIBKITCHENSINK)/libkitchensink.a $(LIBDIR)/$(LIBKITCHENSINK)/pan.o $(LIBDIR)/$(LIBKITCHENSINK)/stove.o

stove:
	$(CC) $(CFLAGS) -o $(BINDIR)/stoved stoved/main.c -L$(LIBDIR)/$(LIBKITCHENSINK) -lkitchensink

clean:
	rm -rf $(LIBDIR)
	rm -rf $(BINDIR)
