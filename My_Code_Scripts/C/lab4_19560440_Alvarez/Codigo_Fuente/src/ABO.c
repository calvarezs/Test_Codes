#include "Includes.h"   

//CONSTRUCTOR
//Tiempo de Ejecución: 14
//Orden  de Ejecución: 0
NodoPadre* CrearNodoPadre(char* Nombre, char* Fono)
{
	NodoPadre* Nuevo;
	Nuevo = (NodoPadre*)malloc(sizeof(NodoPadre));
	Nuevo->Nombre = Nombre;
	Nuevo->Fono = Fono;
	Nuevo->Hijo_Izquierdo = NULL;
	Nuevo->Hijo_Derecho = NULL;
	return Nuevo;
}

//Tiempo de Ejecución: 4
//Orden  de Ejecución: 0
ABO CrearABOVacio()
{
	ABO Nuevo;
	Nuevo.Raiz = NULL;
	return Nuevo;
}

//FUNCION VACIO
//Tiempo: 5
//Orden : 0
int VacioABO(ABO abo)
{
	if(abo.Raiz == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//FUNCION INSERTAR
//Tiempo de Ejecución: 22 + 14n
//Orden  de Ejecución: n
ABO InsertarABO(ABO Arbol, char* Nombre, char* Fono)
{
	NodoPadre* Nuevo;
	Nuevo = CrearNodoPadre(Nombre, Fono);
	NodoPadre* Actual;
	Actual = Arbol.Raiz;
	if(Actual == NULL)
	{
		Arbol.Raiz = Nuevo;
		return Arbol; 
	}
	
	int comparador;
	while(TRUE)
	{
		comparador = strcmp(Nombre, Actual->Nombre);
		if(comparador < 0)
		{
			if(Actual->Hijo_Izquierdo == NULL)
			{
				Actual->Hijo_Izquierdo = Nuevo;
				return Arbol;
			}
			else
			{
				Actual = Actual->Hijo_Izquierdo;
			}
		} 
		else
		{
			if(Actual->Hijo_Derecho == NULL)
			{
				Actual->Hijo_Derecho = Nuevo;
				return Arbol;
			}
			else
			{
				Actual = Actual->Hijo_Derecho;
			}
		} 
	}
}

//FUNCION BUSCAR
//Tiempo de Ejecución: 5 + 45n + 8nn
//Orden  de Ejecución: nn
Lista BuscadorABO(ABO Arbol, Lista Resultante, char* Nombre)
{  
	NodoPadre* Actual = Arbol.Raiz; 
	int comparador;
	while(Actual != NULL)
	{ 
		comparador = strcmp(Nombre, Actual->Nombre); 
		if(comparador == 0)
		{ 
			Resultante = InsertarEnLista(Resultante, Actual->Fono, Resultante.Largo); //33 + 8n
			Actual = Actual->Hijo_Derecho;
		}  
		else if(comparador < 0)
		{ 
			Actual = Actual->Hijo_Izquierdo;
		}
		else
		{ 
			Actual = Actual->Hijo_Derecho;	
		}
	} 
	return Resultante;
}

//SUBFUNCION DE FUNCION DESTRUIR
//Tiempo de Ejecución: 15n - 7
//Orden  de Ejecución: n
void QuemarABO(NodoPadre* Arbol)
{
	if(Arbol == NULL)
	{
		return;
	}
	if(Arbol->Hijo_Izquierdo != NULL)
	{
		QuemarABO(Arbol->Hijo_Izquierdo);	
	}
	else if(Arbol->Hijo_Derecho != NULL)
	{
		QuemarABO(Arbol->Hijo_Derecho);
	} 
	free(Arbol->Nombre);
	free(Arbol->Fono);
	free(Arbol);
	return;
}

//FUNCION DESTRUIR
//Tiempo de Ejecución: 15n - 6
//Orden  de Ejecución: n
void AnularABO(ABO Arbol)
{
	QuemarABO(Arbol.Raiz);
	return;
}


//FUNCION MOSTRAR
//Tiempo de Ejecución: 4n + 6  
//Orden  de Ejecución: n
void PreMostrar(NodoPadre* nodo)
{
	if(nodo == NULL)
	{
		return;
	}
	printf("%s %s\n", nodo->Nombre, nodo->Fono);
	PreMostrar(nodo->Hijo_Izquierdo);
	PreMostrar(nodo->Hijo_Derecho);	
	return;
} 