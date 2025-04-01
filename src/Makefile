IDIR = ../include
CC=gcc
cflags= -I$(IDIR)

ODIR = obj
LDIR = ../lib

LIBS=-lncurses 

_DEPS = game.h update.h render.h util.h entities.h config.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = main.o game.o update.o render.o util.o entities.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

space_invaders: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
