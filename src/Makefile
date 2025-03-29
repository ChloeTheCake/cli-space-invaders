IDIR = ../include
CC=clang
cflags= -I$(IDIR)

ODIR = obj
LDIR = ../lib

LIBS=-lncurses 

_DEPS = projectile.h game.h update.h render.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = main.o projectile.o update.o render.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

space_invaders: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
