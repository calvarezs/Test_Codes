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
ArbolAVL CrearArbolAVLVacio()
{
	ArbolAVL Nuevo;
	Nuevo.Raiz = NULL;
	return Nuevo;
}

//FUNCION VACIO
//Tiempo: 4
//Orden : 0
int VacioArbolAVL(ArbolAVL ArbolAVL)
{
	if(ArbolAVL.Raiz == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//FUNCION ALTURA 
//Tiempo de Ejecución: 32n - 16
//Orden  de Ejecución: n
int Altura(NodoPadre* raiz)
{
	if(raiz == NULL)
	{
		return 0;
	}
	if(raiz->Hijo_Izquierdo == NULL && raiz->Hijo_Derecho == NULL)
	{
		return 0;
	}
	
	int alturaIzquierda = Altura(raiz->Hijo_Izquierdo);
	int alturaDerecha = Altura(raiz->Hijo_Derecho);
	
	if(alturaIzquierda > alturaDerecha)
	{
		return 1 + alturaIzquierda;
	}
	return 1 + alturaDerecha; 
}

//FUNCION DIFERENCIA ALTURAS 
//Tiempo de Ejecución: 64n - 12
//Orden  de Ejecución: n
int DiferenciaAlturas(NodoPadre* raiz)
{
	if(raiz == NULL)
	{
		return 0;
	}
	int alturaIzquierda = 0;
	int alturaDerecha = 0;
	if(raiz->Hijo_Izquierdo != NULL)
	{ 
		alturaIzquierda = Altura(raiz->Hijo_Izquierdo) + 1;
	}
	if(raiz->Hijo_Derecho != NULL)
	{ 
		alturaDerecha = Altura(raiz->Hijo_Derecho) + 1;
	} 
	return alturaIzquierda - alturaDerecha; 
} 

//FUNCION ROTAR A LA DERECHA
//Tiempo de Ejecución: 9
//Orden  de Ejecución: 0 
NodoPadre* RotarDerecha(NodoPadre* raiz)
{
	NodoPadre* nuevo = raiz->Hijo_Izquierdo;
	raiz->Hijo_Izquierdo = nuevo->Hijo_Derecho;
	nuevo->Hijo_Derecho = raiz;
	return nuevo;
} 
 
//FUNCION ROTAR A LA IZQUIERDA
//Tiempo de Ejecución: 9
//Orden  de Ejecución: 0
NodoPadre* RotarIzquierda(NodoPadre* raiz)
{
	NodoPadre* nuevo = raiz->Hijo_Derecho;
	raiz->Hijo_Derecho = nuevo->Hijo_Izquierdo;
	nuevo->Hijo_Izquierdo = raiz;
	return nuevo;
} 
//FUNCION EQUILIBRAR
//Tiempo de Ejecución: 12 nn + 64n + 38 
//Orden  de Ejecución: nn
NodoPadre* Equilibrar(NodoPadre* raiz)
{	
	if(raiz == NULL || Altura(raiz) < 2)
	{
		return raiz;
	}
	
	raiz->Hijo_Izquierdo = Equilibrar(raiz->Hijo_Izquierdo);
	raiz->Hijo_Derecho = Equilibrar(raiz->Hijo_Derecho);
	
	int diferencia = DiferenciaAlturas(raiz);
	if(diferencia == 2)
	{
		if(DiferenciaAlturas(raiz->Hijo_Izquierdo) < 0)
		{
			raiz->Hijo_Izquierdo = RotarIzquierda(raiz->Hijo_Izquierdo);
		}
		return RotarDerecha(raiz);
	}
	else if(diferencia == -2)
	{
		if(DiferenciaAlturas(raiz->Hijo_Izquierdo) > 0)
		{
			raiz->Hijo_Derecho = RotarDerecha(raiz->Hijo_Derecho);
		}
		return RotarIzquierda(raiz);
	}   
	return raiz;
}

//FUNCION INSERTAR
//Tiempo de Ejecución: 23 + 11n
//Orden  de Ejecución: n
ArbolAVL InsertarArbolAVL(ArbolAVL Arbol, char* Nombre, char* Fono)
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
				Arbol.Raiz = Equilibrar(Arbol.Raiz);
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
				Arbol.Raiz = Equilibrar(Arbol.Raiz);
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
//Tiempo de Ejecución: 7 + 34n + 8nn
//Orden  de Ejecución: nn
Lista BuscadorArbolAVL(ArbolAVL Arbol, Lista Resultante, char* Nombre)
{  
	NodoPadre* Actual = Arbol.Raiz; 
	int comparador;
	while(Actual != NULL)
	{ 
		comparador = strcmp(Nombre, Actual->Nombre); 
		if(comparador == 0)
		{ 
			Resultante = InsertarEnLista(Resultante, Actual->Fono, Resultante.Largo); //20 + 8n
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
void QuemarArbolAVL(NodoPadre* Arbol)
{
	if(Arbol == NULL)
	{
		return;
	}
	if(Arbol->Hijo_Izquierdo != NULL)
	{
		QuemarArbolAVL(Arbol->Hijo_Izquierdo);	
	}
	else if(Arbol->Hijo_Derecho != NULL)
	{
		QuemarArbolAVL(Arbol->Hijo_Derecho);
	} 
	free(Arbol->Nombre);
	free(Arbol->Fono);
	free(Arbol);
	return;
}

//FUNCION DESTRUIR
//Tiempo de Ejecución: 15n - 6
//Orden  de Ejecución: n
void AnularArbolAVL(ArbolAVL Arbol)
{
	QuemarArbolAVL(Arbol.Raiz);
	return;
}


//FUNCION MOSTRAR
//Tiempo de Ejecución: 4n + 1
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

//FUNCION IMPRIMIR
//Subfuncion
void imprimirPreOrden(NodoPadre* nodo, int nivel)
{  
	if (nodo == NULL)
	{ 
		return;
	}
	 
	printf("*Nivel: %d\n", nivel);
	printf("Nombre: %s\n", nodo->Nombre);
	printf("Fono  : %s\n", nodo->Fono);
	if(nodo->Hijo_Izquierdo != NULL)
	{
		printf("Nombre Hijo Izquierdo  : %s\n", nodo->Hijo_Izquierdo->Nombre);
		printf("Telefono Hijo Izquierdo: %s\n", nodo->Hijo_Izquierdo->Fono);
	}
	else
	{
		printf("Nombre Hijo Izquierdo  : none\n");
		printf("Telefono Hijo Izquierdo: none\n");
	}
	if(nodo->Hijo_Derecho != NULL)
	{
		printf("Nombre Hijo Derecho  : %s\n", nodo->Hijo_Derecho->Nombre); 
		printf("Telefono Hijo Derecho: %s\n", nodo->Hijo_Derecho->Fono);
	}
	else
	{
		printf("Nombre Hijo Izquierdo  : none\n");
		printf("Telefono Hijo Izquierdo: none\n");
	}
	printf("\n");
	imprimirPreOrden(nodo->Hijo_Izquierdo, nivel + 1);
	imprimirPreOrden(nodo->Hijo_Derecho, nivel + 1);
	return;
}

//FUNCION MASCARA PRINCIPAL
//Tiempo de Ejecución: 5 +  
//Orden  de Ejecución: 
void PreImpresion(ArbolAVL Arbol)
{ 
	imprimirPreOrden(Arbol.Raiz, 0); 
	return;
}