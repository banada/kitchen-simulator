CC=gcc
CFLAGS= -g -Wall

LIBDIR=$(PWD)/lib
LIBKITCHENSINK=libkitchensink

BINDIR=$(PWD)/bin


all: setup omelette stove fridge test

setup:
	mkdir -p $(LIBDIR)/$(LIBKITCHENSINK)
	mkdir -p $(BINDIR)

omelette: libkitchensink
	$(CC) $(CFLAGS) -o $(BINDIR)/omelette omelette.c -L$(LIBDIR)/$(LIBKITCHENSINK) -lkitchensink

libkitchensink:
	$(CC) -o $(LIBDIR)/$(LIBKITCHENSINK)/pan.o -c pan.c
	$(CC) -o $(LIBDIR)/$(LIBKITCHENSINK)/food.o -c food.c
	$(CC) -o $(LIBDIR)/$(LIBKITCHENSINK)/stove.o -c stoved/stove.c
	$(CC) -o $(LIBDIR)/$(LIBKITCHENSINK)/fridge.o -c fridged/fridge.c
	ar -cvq $(LIBDIR)/$(LIBKITCHENSINK)/libkitchensink.a $(LIBDIR)/$(LIBKITCHENSINK)/pan.o $(LIBDIR)/$(LIBKITCHENSINK)/food.o $(LIBDIR)/$(LIBKITCHENSINK)/stove.o $(LIBDIR)/$(LIBKITCHENSINK)/fridge.o

stove:
	$(CC) $(CFLAGS) -o $(BINDIR)/stoved stoved/main.c -L$(LIBDIR)/$(LIBKITCHENSINK) -lkitchensink -lsystemd

fridge:
	$(CC) $(CFLAGS) -o $(BINDIR)/fridged fridged/main.c -L$(LIBDIR)/$(LIBKITCHENSINK) -lkitchensink -lsystemd

test:
	$(CC) $(CFLAGS) -o $(BINDIR)/test-stove tests/test-stove.c -L$(LIBDIR)/$(LIBKITCHENSINK) -lkitchensink

clean:
	rm -rf $(LIBDIR)
	rm -rf $(BINDIR)
