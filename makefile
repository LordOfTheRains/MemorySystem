IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =../lib

LIBS=-lm

_DEPS = page.h tlb.h address.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = address.o page.o tlb.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vm_sim: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
