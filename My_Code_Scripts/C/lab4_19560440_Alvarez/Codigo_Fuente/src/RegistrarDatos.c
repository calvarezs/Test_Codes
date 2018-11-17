#include "Includes.h"  

//Funcion que ingresa los datos obtenidos desde un archivo de datos indicado a un elemento
//del tipo de dato arbol binario
//Entradas: Un arbol binario vacio y el nombre del archivo sobre el cual se van a obtener 
//			los datos
//Salidas: Un arbol binario con los datos nuevos
//Tiempo de ejecucion: 30 + 35n + 14nn
//Orden de ejecucion : nn
ABO RegistrarDatos(ABO Datos, char* NombreArchivoDatos)
{
	FILE* Archivo; 
	
	Archivo = fopen(NombreArchivoDatos, "r");
	if(!Archivo)
	{
		printf("Error 404: FILE '%s' NOT FOUND\n", NombreArchivoDatos);
		return Datos;
	}

	char* s2 = (char*) calloc(LARGO_NOMBRE*sizeof(char),1);
	char* s3 = (char*) calloc(LARGO_NOMBRE*sizeof(char),1);
	char* s4 = (char*) calloc(LARGO_NOMBRE*sizeof(char),1);
	char* aux = (char*) calloc(LARGO_AUXILIAR*sizeof(char),1); 

	while(!feof(Archivo))
	{
		char* Nombre = (char*) calloc(LARGO_NOMBRE_COMPLETO*sizeof(char),1);
		char* Fono = (char*) calloc(LARGO_NOMBRE*sizeof(char),1); 

		fscanf(Archivo, "%s %s %s %s %[ ]", Nombre, s2, s3, s4, aux); 
		fscanf(Archivo, "%[+0-9 ] %[\n]", Fono, aux);

		strcat(Nombre, " ");
		strcat(Nombre, s2);
		strcat(Nombre, " ");
		strcat(Nombre, s3);
		strcat(Nombre, " ");
		strcat(Nombre, s4); 
 
		Datos = InsertarABO(Datos, Nombre, Fono); //22 + 14n 
	} 
	return Datos;
}
