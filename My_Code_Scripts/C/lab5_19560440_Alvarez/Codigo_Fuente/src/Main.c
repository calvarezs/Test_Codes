#include "Includes.h"  
#include <time.h>

//Bloque Principal del programa
//Nota: el tiempo de ejecucion de cada funcionalidad del programa esta indicado a un costado de su invocación
//Tiempo de ejecucion: 22 mas las funciones
//Orden de ejecucion : nnn
int main()
{
	printf("**********INICIO DEL PROGRAMA***********\n");
	clock_t t_ini, t_fin;
	double secs;
	t_ini = clock();
	
	ArbolAVL Directorio;
	Lista ContactosEncontrados;
	char* NombreArchivoDatos;
	char* NombreArchivoArbol;
	char* NombreArchivoRequeridos;
	char* NombreArchivoSalida;
	
	//A continuacion se indican los nombres de los archivos
	NombreArchivoDatos = "Telefonos.in";
	NombreArchivoArbol = "Arbol.out";
	NombreArchivoRequeridos = "Buscados.in";
	NombreArchivoSalida = "TelefonosEncontrados.out";
	
	//////Fase 1: Crear arbol binario vacio//////
	printf("Iniciando arbol binario\n");
	Directorio = CrearArbolAVLVacio(); //T(CrearArbolAVLVacio) = 4
	
	//////Fase 2: Copiar los datos del archivo de entrada en el arbol binario//////  
	printf("Almacenando datos\n");
	Directorio = RegistrarDatos(Directorio, NombreArchivoDatos); //T(RegistrarDatos) = 8 + 53n + 11nn 

	//En caso de falla salir
	if(VacioArbolAVL(Directorio))
	{
		printf("****TERMINO DEL PROGRAMA CON ERRORES****\n");
		return -1;
	} 

	//////Fase 3: Localizar los contactos del arbol binario//////
	printf("Localizando contactos\n"); 
	ContactosEncontrados = LocalizarContactos(Directorio, NombreArchivoRequeridos); //T(LocalizarContactos) = 

	//En caso de falla salir
	if(Vacio(ContactosEncontrados))
	{
		printf("****TERMINO DEL PROGRAMA CON ERRORES****\n");
		return -1;
	}

	//////Fase 4.1: Imprimir el arbol completo//////
	printf("Imprimiendo Arbol\n\n\n"); 
	PreImpresion(Directorio);

	//////Fase 4.2: Imprimir los contactos localizados//////
	printf("Preparando Archivo Salida\n"); 
	ImprimirContactos(ContactosEncontrados, NombreArchivoSalida); //T(ImprimirContactos) = 12 + 30n + 8nn

	////No olvidar liberar la memoria////
	printf("Terminando elementos del programa utilizados\n"); 
	AnularArbolAVL(Directorio); //15n - 6 
	AnularLista(ContactosEncontrados); //7 + 7n
	
    
	
	t_fin = clock();
	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	printf("%.16g milisegundos\n", secs * 1000.0);
	printf("Fin de programa. Presione Enter para terminar.\n");
	getchar();
	printf("**********TERMINO DEL PROGRAMA**********\n");
	return 0;
} 