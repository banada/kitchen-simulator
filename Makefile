CC=gcc
CFLAGS= -g -Wall

LIBDIR=$(PWD)/lib
LIBKITCHEN=libkitchen

BINDIR=$(PWD)/bin


all: setup omelette

setup:
	mkdir -p $(LIBDIR)/$(LIBKITCHEN)
	mkdir -p $(BINDIR)

omelette: libkitchen
	$(CC) $(CFLAGS) -o $(BINDIR)/omelette omelette.c -L$(LIBDIR)/$(LIBKITCHEN) -lkitchen

libkitchen: kitchen.c
	$(CC) -o $(LIBDIR)/$(LIBKITCHEN)/kitchen.o -c kitchen.c
	ar -cvq $(LIBDIR)/$(LIBKITCHEN)/libkitchen.a $(LIBDIR)/$(LIBKITCHEN)/kitchen.o

clean:
	rm -rf $(LIBDIR)
	rm -rf $(BINDIR)
