IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib 


_DEPS = Includes.h Lista.h ArbolAVL.h RegistrarDatos.h LocalizarContactos.h ImprimirContactos.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Main.o Lista.o ArbolAVL.o RegistrarDatos.o LocalizarContactos.o ImprimirContactos.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#Para Linux intercambiar a Laberinto.out
#Para Windows intercambiar a Laberinto.exe
#Ejecucion usando el comando 'make' en terminal o bloque de comandos segun corresponda
Laberinto.exe: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) 

.PHONY: clean

#Ejecutar comando 'make clean' en caso de cambio de código o cambio del sistema operativo usado

clean:
	rm -f $(ODIR)/*.o *.exe *.out