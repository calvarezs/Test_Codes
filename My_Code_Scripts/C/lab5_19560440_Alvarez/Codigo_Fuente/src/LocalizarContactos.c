#include "Includes.h"  

//Funcion que en base a un arbol binario, localiza los contactos indicados en un archivo de texto indicado
//como parametro de entrada
//Entradas: -Un arbol binario con datos
//			-Un arreglo de caracteres con el nombre del archivo a revisar
//Salidas:	-Una lista con arreglos de caracteres que representan la respuesta al problema presentado 
//Tiempo de ejecucion: 42 + 67n + 82nn + 8nnn
//Orden de ejecucion : 
Lista LocalizarContactos(ArbolAVL Datos, char* NombreArchivoRequeridos)
{
	FILE* Archivo;
	Lista resultante;

	//Cadenas auxiliares de char contenedoras del nombre a buscar
	char* s2 = (char*) calloc(LARGO_NOMBRE*sizeof(char),1);
	char* s3 = (char*) calloc(LARGO_NOMBRE*sizeof(char),1);
	char* s4 = (char*) calloc(LARGO_NOMBRE*sizeof(char),1);
	char* aux = (char*) calloc(LARGO_AUXILIAR*sizeof(char),1);

	Archivo = fopen(NombreArchivoRequeridos, "r");

	resultante = CrearLista();//10

	if(!Archivo)
	{
		printf("Error 404: FILE '%s' NOT FOUND\n", NombreArchivoRequeridos);
		return resultante;
	}

	while(!feof(Archivo))
	{
		char* NombreABuscar = (char*) calloc(LARGO_NOMBRE_COMPLETO*sizeof(char),1); 
		
		Lista contactoEncontrado;
		contactoEncontrado = CrearLista();//10

		fscanf(Archivo, "%s %s %s %s %[\n]", NombreABuscar, s2, s3, s4, aux);  

		strcat(NombreABuscar, " ");
		strcat(NombreABuscar, s2);
		strcat(NombreABuscar, " ");
		strcat(NombreABuscar, s3);
		strcat(NombreABuscar, " ");
		strcat(NombreABuscar, s4);  

		contactoEncontrado = BuscadorArbolAVL(Datos, contactoEncontrado, NombreABuscar);//7 + 34n + 8nn  

		resultante = InsertarEnLista(resultante, NombreABuscar, resultante.Largo); //12 + 22n
		if(Vacio(contactoEncontrado))
		{
			char* SinResultado = (char*) malloc(sizeof(char)*15);
			strcpy( SinResultado, "Sin Resultados"); 
			resultante = InsertarEnLista(resultante, SinResultado, resultante.Largo); //12 + 22n
		}
		resultante = ConcatenarLista(resultante, contactoEncontrado);//21 + 5n  
		char* none = (char*) malloc(sizeof(char)*5);
		strcpy(none, "none");
		resultante = InsertarEnLista(resultante, none, resultante.Largo); //12 + 22n 
	}

	return resultante;
}

