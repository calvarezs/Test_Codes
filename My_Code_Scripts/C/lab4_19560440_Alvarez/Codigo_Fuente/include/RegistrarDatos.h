#ifndef REGISTRAR_DATOS_H
#define REGISTRAR_DATOS_H
#include "Includes.h"
//Funcion que ingresa los datos obtenidos desde un archivo de datos indicado a un elemento
//del tipo de dato arbol binario
//Entradas: Un arbol binario vacio y el nombre del archivo sobre el cual se van a obtener 
//			los datos
//Salidas: Un arbol binario con los datos nuevos
//Tiempo de ejecucion: 30 + 35n + 14nn
//Orden de ejecucion : nn
ABO RegistrarDatos(ABO Datos, char* NombreArchivoDatos);
#endif