#include "Includes.h"  

//CONSTRUCTOR
//Tiempo de Ejecución: 10
//Orden de Ejecución : 0
Nodo* CrearNodoLista(char* Palabra)
{
	Nodo* Nueva;
	Nueva = (Nodo*)malloc(sizeof(Nodo));
	Nueva->Palabra = Palabra;
	Nueva->Siguiente = NULL;
	return Nueva;
}

//Tiempo de Ejecución: 6
//Orden de Ejecución : 0
Lista CrearLista()
{
	Lista Nueva; 
	Nueva.Cabeza = NULL;
	Nueva.Largo = 0;
	return Nueva;
} 

//FUNCION VACIO
//Tiempo: 5
//Orden : 0
int Vacio(Lista lista)
{
	if(lista.Cabeza == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//FUNCION INSERTAR
//Tiempo de Ejecución: 33 + 8n     
//Orden de Ejecución : n
Lista InsertarEnLista(Lista lista, char* Palabra, int pos)
{
	Nodo* nodoNuevo; 
	Nodo* nodoGuia;
	if (pos<0)
	{
		return lista;
	}
	if (pos==0)
	{
		nodoNuevo = CrearNodoLista(Palabra);  
		nodoNuevo->Siguiente = lista.Cabeza;
		lista.Cabeza = nodoNuevo;  
		lista.Largo++;
		return lista;
	}
	int i = 1;
	nodoGuia = lista.Cabeza;
	while(nodoGuia!=NULL && i!=pos)
	{
		nodoGuia = nodoGuia->Siguiente;
		i++;
	} 
	if(nodoGuia!=NULL)
	{
		nodoNuevo = CrearNodoLista(Palabra); 
		nodoNuevo->Siguiente = nodoGuia->Siguiente;
		nodoGuia->Siguiente = nodoNuevo;
		lista.Largo++;
	} 
	return lista;
}

//FUNCION CONCATENAR
//Tiempo de Ejecución: 22 + 5n
//Orden de Ejecución : n
Lista ConcatenarLista(Lista lista1, Lista lista2)
{
	Nodo* Auxiliar = lista1.Cabeza;
	Nodo* Nuevo = lista2.Cabeza;
	if(Auxiliar == NULL)
	{
		return lista2;
	}
	else if(Nuevo == NULL)
	{
		return lista1;
	}
	int pos = lista1.Largo;
	while(Auxiliar->Siguiente!=NULL)
	{
		Auxiliar = Auxiliar->Siguiente;
	}
	Auxiliar->Siguiente = Nuevo; 
	lista1.Largo += lista2.Largo;
	return lista1;
}

//FUNCION OBTENER
//Tiempo de Ejecución: 11 + 8n
//Orden de Ejecución : n
char* ObtenerEnLista(Lista lista, int indice)
{
	Nodo* nodoActual;
	int contador;
	nodoActual = lista.Cabeza;
	contador = 0;
	
	if(indice < 0 || indice >= lista.Largo)
	{
		return NULL;
	}
	
	while(nodoActual != NULL)
	{
		if(contador == indice)
		{
			return nodoActual->Palabra;
		}
		contador++;
		nodoActual = nodoActual->Siguiente;
	}
	
	return NULL;
}

//FUNCION MOSTRAR
//Tiempo de Ejecución: 6 + 6n
//Orden  de Ejecucion: n
void MostrarLista(Lista lista)
{
	Nodo* Actual = lista.Cabeza;
	printf("Inicio Lista:\n");
	while(Actual != NULL)
	{
		printf("%s\n", Actual->Palabra);
		Actual = Actual->Siguiente;
	}
	printf("Fin Lista\n");
	return;
} 

//FUNCION ANULAR
//Tiempo de Ejecución: 7 + 11n
//Orden de Ejecución : n
void AnularLista(Lista lista)
{
	Nodo* Actual = lista.Cabeza;
	Nodo* Auxiliar;  

	while(Actual!=NULL)
	{  
		Auxiliar = Actual;
		lista.Cabeza = Actual->Siguiente;
		Actual = lista.Cabeza;
		free(Auxiliar->Palabra);
		free(Auxiliar);
	} 
	lista.Largo = 0;
	return;
} 