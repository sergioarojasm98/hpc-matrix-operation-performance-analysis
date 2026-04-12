GCC = mpicc
oT = -fopenmp -O3 

CFLAGS = -lm 

oL= Otime.c

BINDIR = ../BIN/
PROGS = $(BINDIR)MM1f 

all: MM1f

clean:
	$(RM) $(PROGS)

MM1f:
	$(GCC) $(oT) $(oL) $@.c -o $(BINDIR)$@ $(CFLAGS)
