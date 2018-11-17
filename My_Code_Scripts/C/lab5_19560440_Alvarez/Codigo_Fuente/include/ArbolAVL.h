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

//Tipo de dato ArbolAVL (arbol binario ordenado)
typedef struct ArbolAVL
{
	NodoPadre* Raiz;
}ArbolAVL;

//CONSTRUCTOR
//Tiempo de Ejecución: 14
//Orden  de Ejecución: 0
NodoPadre* CrearNodoPadre(char* Nombre, char* Fono);

//Tiempo de Ejecución: 4
//Orden  de Ejecución: 0
ArbolAVL CrearArbolAVLVacio();

//FUNCION VACIO
//Tiempo: 4
//Orden : 0
int VacioArbolAVL(ArbolAVL ArbolAVL);

//FUNCION INSERTAR
//Tiempo de Ejecución: 
//Orden  de Ejecución: n
ArbolAVL InsertarArbolAVL(ArbolAVL Arbol, char* Nombre, char* Fono);

//FUNCION BUSCAR
//Tiempo de Ejecución: 7 + 34n + 8nn
//Orden  de Ejecución: nn
Lista BuscadorArbolAVL(ArbolAVL Arbol, Lista Resultante, char* Nombre);

//FUNCION DESTRUIR
//Tiempo de Ejecución: 15n - 6
//Orden  de Ejecución: n
void AnularArbolAVL(ArbolAVL Arbol);

//FUNCION MOSTRAR
//Tiempo de Ejecución: 4n + 1
//Orden  de Ejecución: n
void PreMostrar(NodoPadre* nodo);

//FUNCION IMPRIMIR
//Tiempo de Ejecución: 
//Orden  de Ejecución: 
void PreImpresion(ArbolAVL Arbol);

#endif