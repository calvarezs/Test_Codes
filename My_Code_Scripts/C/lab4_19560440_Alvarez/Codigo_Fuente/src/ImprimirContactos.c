#include "Includes.h"  

//Procedimiento que imprime una serie de contactos en un archivo de texto indicado como parametro de entrada
//Entradas: -Una lista que contiene una serie de elementos string a imprimir: 
//					para separar entre lineas de impresion se usa el separador "none"
//			-Un string con el nombre del archivo de texto sobre el cual se van a imprimir los resultados
//Salidas:	-Ninguna
//Tiempo de ejecucion: 12 + 28n + 8nn
//Orden de ejecucion : nn
void ImprimirContactos(Lista ContactosEncontrados, char* NombreArchivoSalida)
{
	FILE* ArchivoSalida;
	int posicionador, largoLista;
	char* elementoARevisar;

	ArchivoSalida = fopen(NombreArchivoSalida, "wt");
	largoLista = ContactosEncontrados.Largo;
	posicionador = 1;

	int i;
	for(i=0; i<largoLista; i++)
	{
		elementoARevisar = ObtenerEnLista(ContactosEncontrados, i); // T(Obtener(Lista,int)) = 11 + 8n
		if(strcmp(elementoARevisar, "none") == 0)
		{
			fprintf(ArchivoSalida, "\n"); 
			posicionador = 1;
		}
		else if(posicionador == 1)
		{
			fprintf(ArchivoSalida, "%s: ", elementoARevisar); 
			posicionador = 2;
		}
		else if(posicionador == 2)
		{
			fprintf(ArchivoSalida, "%s", elementoARevisar); 
			posicionador = 3;
		}
		else
		{
			fprintf(ArchivoSalida, " - %s", elementoARevisar); 
		}
	}
	fclose(ArchivoSalida);
	return;
}