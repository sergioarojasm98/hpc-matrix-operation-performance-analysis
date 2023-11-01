CC = mpicc                 # Utiliza el compilador MPI
oT = -fopenmp -O3          # Directivas para OpenMP y optimización

CFLAGS = -lm               # Librerías, -lm es para la biblioteca matemática

oL = Otime.c               # Otros archivos fuente

BINDIR = ../BIN/
PROGS = $(BINDIR)MM1c

all: MM1c

clean:
	$(RM) $(PROGS)

MM1c:
	$(CC) $(oT) $(oL) $@.c -o $(BINDIR)$@ $(CFLAGS)
