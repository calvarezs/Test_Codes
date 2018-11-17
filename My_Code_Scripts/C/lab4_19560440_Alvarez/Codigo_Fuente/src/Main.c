#include "Includes.h"  
#include <time.h>

//Bloque Principal del programa
//Nota: el tiempo de ejecucion de cada funcionalidad del programa esta indicado a un costado de su invocación
//Tiempo de ejecucion: 120 + 241n + 96nn + 8nnn
//Orden de ejecucion : nnn
int main()
{
	printf("**********INICIO DEL PROGRAMA***********\n");
	clock_t t_ini, t_fin;
	double secs;
	t_ini = clock();
	
	ABO Directorio;
	Lista ContactosEncontrados;
	char* NombreArchivoDatos;
	char* NombreArchivoRequeridos;
	char* NombreArchivoSalida;
	
	//A continuacion se indican los nombres de los archivos
	NombreArchivoDatos = "Telefonos.in";
	NombreArchivoRequeridos = "Buscados.in";
	NombreArchivoSalida = "TelefonosEncontrados.out";
	
	//////Fase 1: Crear arbol binario vacio//////
	printf("Iniciando arbol binario\n");
	Directorio = CrearABOVacio(); //T(CrearABOVacio) = 5
	
	//////Fase 2: Copiar los datos del archivo de entrada en el arbol binario//////  
	printf("Almacenando datos\n");
	Directorio = RegistrarDatos(Directorio, NombreArchivoDatos); //T(RegistrarDatos) = 30 + 35n + 14nn

	//En caso de falla salir
	if(VacioABO(Directorio))
	{
		printf("****TERMINO DEL PROGRAMA CON ERRORES****\n");
		return -1;
	} 

	//////Fase 3: Localizar los contactos del arbol binario//////
	printf("Localizando contactos\n"); 
	ContactosEncontrados = LocalizarContactos(Directorio, NombreArchivoRequeridos); //T(LocalizarContactos) = 41 + 152n + 74nn + 8nnn
	//En caso de falla salir
	if(Vacio(ContactosEncontrados))
	{
		printf("****TERMINO DEL PROGRAMA CON ERRORES****\n");
		return -1;
	}

	//////Fase 4: Imprimir los contactos localizados//////
	printf("Preparando Archivo Salida.out\n"); 
	ImprimirContactos(ContactosEncontrados, NombreArchivoSalida); //T(ImprimirContactos) = 12 + 28n + 8nn

	////No olvidar liberar la memoria////
	printf("Terminando elementos del programa utilizados\n"); 
	AnularABO(Directorio); //15n - 6 
	AnularLista(ContactosEncontrados); //7 + 11n
	
	t_fin = clock();

	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	printf("%.16g milisegundos\n", secs * 1000.0);
	getchar();
    printf("**********TERMINO DEL PROGRAMA**********\n");
	return 0;
} 