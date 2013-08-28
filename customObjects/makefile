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
LDFLAGS=-lm -lstdc++

ODIR=obj
LDIR=lib
BDIR=bin
SDIR=src

EXE=$(BDIR)/exec

_LIB=Vector2.h Vector3.h Matrix2x2.h Matrix3x3.h matrixmath.h
LIB=$(patsubst %,$(LDIR)/%,$(_LIB))

_OBJ=main.o Vector2.o Vector3.o Matrix2x2.o Matrix3x3.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(LIB)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(EXE): $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXE)