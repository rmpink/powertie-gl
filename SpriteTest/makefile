#
# PROJECT:
# FILEPATH:
# AUTHOR:
# DATE CREATED:
# DATE MODIFIED:
#
# DESCRIPTION:
#
#
#

CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLU -lglut -lGLEW -lIL -lILU -lfreetype -lstdc++ -lm

ODIR=obj
LDIR=lib
BDIR=bin
SDIR=src

EXE=$(BDIR)/exec

_LIB=initGL.h const.h utilities.h texture.h spriteSheet.h Vector2.h Entity.h Actor.h
LIB=$(patsubst %,$(LDIR)/%,$(_LIB))

_OBJ=main.o utilities.o texture.o spriteSheet.o Vector2.o Entity.o Actor.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(LIB)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXE)