#ifndef IMPRIMIR_CONTACTOS_H
#define IMPRIMIR_CONTACTOS_H
#include "Includes.h"
//Procedimiento que imprime una serie de contactos en un archivo de texto indicado como parametro de entrada
//Entradas: -Una lista que contiene una serie de elementos string a imprimir: 
//					para separar entre lineas de impresion se usa el separador "none"
//			-Un string con el nombre del archivo de texto sobre el cual se van a imprimir los resultados
//Salidas:	-Ninguna
//Tiempo de ejecucion: 12 + 28n + 8nn
//Orden de ejecucion : nn
void ImprimirContactos(Lista ContactosEncontrados, char* NombreArchivoSalida);
#endif