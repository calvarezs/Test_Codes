#ifndef LOCALIZAR_CONTACTOS_H
#define LOCALIZAR_CONTACTOS_H
#include "Includes.h"
//Funcion que en base a un arbol binario, localiza los contactos indicados en un archivo de texto indicado
//como parametro de entrada
//Entradas: -Un arbol binario con datos
//			-Un arreglo de caracteres con el nombre del archivo a revisar
//Salidas:	-Una lista con arreglos de caracteres que representan la respuesta al problema presentado 
//Tiempo de ejecucion: 41 + 152n + 74nn + 8nnn   
//Orden de ejecucion : nnn
Lista LocalizarContactos(ABO Datos, char* NombreArchivoRequeridos);
#endif