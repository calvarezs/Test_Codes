#ifndef ARBOL_BIN_H
#define ARBOL_BIN_H
#include "Includes.h"

//Tipo de dato nodo Padre con dos descendientes 
typedef struct NodoPadre
{
	char* Nombre;
	char* Fono;
	struct NodoPadre* Hijo_Izquierdo;
	struct NodoPadre* Hijo_Derecho;
}NodoPadre;

//Tipo de dato ABO (arbol binario ordenado)
typedef struct ABO
{
	NodoPadre* Raiz;
}ABO;

//CONSTRUCTOR
//Tiempo de Ejecución: 14
//Orden  de Ejecución: 0
NodoPadre* CrearNodoPadre(char* Nombre, char* Fono);

//Tiempo de Ejecución: 4
//Orden  de Ejecución: 0
ABO CrearABOVacio();

//FUNCION VACIO
//Tiempo: 5
//Orden : 0
int VacioABO(ABO abo);

//FUNCION INSERTAR
//Tiempo de Ejecución: 22 + 14n
//Orden  de Ejecución: n
ABO InsertarABO(ABO Arbol, char* Nombre, char* Fono);

//FUNCION BUSCAR
//Tiempo de Ejecución: 5 + 45n + 8nn
//Orden  de Ejecución: nn
Lista BuscadorABO(ABO Arbol, Lista Resultante, char* Nombre);

//FUNCION ANULAR
//Tiempo de Ejecución: 15n - 6
//Orden  de Ejecución: n
void AnularABO(ABO Arbol);

//FUNCION MOSTRAR
//Tiempo de Ejecución: 4n + 6
//Orden  de Ejecución: n
void PreMostrar(NodoPadre* nodo);

#endif