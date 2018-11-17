#ifndef LISTA_H
#define LISTA_H
#include "Includes.h"
//TDA de una lista enlazada por punteros utilizada para almacenar arreglos de strings

//DEFINCION NODO:
typedef struct Nodo
{
	char* Palabra;
	struct Nodo* Siguiente;
}Nodo;  

//DEFINCION LISTA
typedef struct Lista
{
	Nodo* Cabeza;
	int Largo;
}Lista;

//CONSTRUCTOR
//Tiempo de Ejecución: 10
//Orden de Ejecución : 0
Nodo* CrearNodoLista(char* Palabra);

//Tiempo de Ejecución: 6
//Orden de Ejecución : 0
Lista CrearLista();

//FUNCION VACIO
//Tiempo: 4
//Orden : 0
int Vacio(Lista lista);

//FUNCION INSERTAR
//Tiempo de Ejecución: 32 + 8n
//Orden de Ejecución : n
Lista InsertarEnLista(Lista lista, char* Palabra, int pos);

//FUNCION CONCATENAR
//Tiempo de Ejecución: 21 + 5n
//Orden de Ejecución : n
Lista ConcatenarLista(Lista lista1, Lista lista2);

//FUNCION OBTENER
//Tiempo de Ejecución: 12 + 8n
//Orden de Ejecución : n
char* ObtenerEnLista(Lista lista, int indice);

//FUNCION MOSTRAR
//Tiempo de Ejecución: 6 + 6n
//Orden  de Ejecucion: n
void MostrarLista(Lista lista);

//FUNCION ANULAR
//Tiempo de Ejecución: 7 + 11n
//Orden de Ejecución : n
void AnularLista(Lista lista);

#endif