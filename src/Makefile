IDIR = ../include
CC=gcc
cflags= -I$(IDIR)

ODIR = obj
LDIR = ../lib

LIBS=-lncurses 

_DEPS = util.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = main.o util.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

space_invaders: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
