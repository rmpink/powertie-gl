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

_LIB=texture.h initGL.h utilities.h const.h clip.h colour.h texture.h particleEmitter.h mask.h collisionMask.h
LIB=$(patsubst %,$(LDIR)/%,$(_LIB))

_OBJ=main.o utilities.o texture.o particleEmitter.o collisionMask.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(LIB)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -vf $(ODIR)/* $(BDIR)/*