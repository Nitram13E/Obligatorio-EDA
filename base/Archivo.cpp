#include<stdlib.h>
#include"Archivo.h"

/*
    1) El manejador sólo permitirá trabajar con un archivo de texto y sus diferentes versiones.
    2) Las versiones se identifican de manera unívoca por una secuencia de 1 o más números separados por un punto. Estos números pueden ser de más de 1 dígito y no hay límite en la secuencia de números. Las versiones nunca empiezan ni terminan con un punto. Algunos ejemplos son: 4, 2.3, 4.12.3.21, 1.2.3.4.5.6.7.8.9.10.11
    3) Cada versión puede tener 0, 1 ó más subversiones dependientes.
    4) Una versión depende y tiene como padre una sola versión, excepto las versiones iniciales del archivo (correspondientes a los números: 1, 2, 3…).
    5) Cada versión X de un archivo incorpora 0, 1 o más modificaciones a la versión padre (si existe) de X.
    6) En el sistema se distingue el uso de minúsculas y mayúsculas. Por ejemplo CASA ? Casa ? casa.
    7) Solo se puede usar la librería stdio.h en el archivo cpp que contenga la función main(). Sólo se puede utilizar para debug, nada más. Pero la entrega final no lo puede incluir.
    8) Los grupos son de 3 personas. Sólo puede caber la posibilidad de uno o dos grupos de 2 personas, en caso de que la cantidad de estudiantes no sea múltiplo de tres.
*/



//Crear el archivo.
Archivo CrearArchivo(char * nombre){
    return NULL;
}

//Borrar el archivo.
TipoRet BorrarArchivo(Archivo &a){
    return NO_IMPLEMENTADA;
}

//Crear una nueva versión.
TipoRet CrearVersion(Archivo &a, char * version, char * error){
    return NO_IMPLEMENTADA;
}

//Borrar una versión, junto con sus hijos (subversiones), liberando toda la memoria involucrada.
TipoRet BorrarVersion(Archivo &a, char * version){
    return NO_IMPLEMENTADA;
}

//Mostrar todas las versiones de un archivo de forma jerárquica.
TipoRet MostrarVersiones(Archivo a){
    return NO_IMPLEMENTADA;
}

//Operaciones Relativas al Texto:

//Insertar una línea de texto, en cierta posición, a una versión de un archivo.
TipoRet  InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * error){
    return NO_IMPLEMENTADA;
}

//Borrar una línea de texto, en cierta posición, a una versión de un archivo.
TipoRet  BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error){
    return NO_IMPLEMENTADA;
}

//Mostrar el texto completo de una versión.
TipoRet  MostrarTexto(Archivo a, char * version){
    return NO_IMPLEMENTADA;
}

//Mostrar todas las modificaciones en el texto de una versión X, respecto a la versión padre de X.
TipoRet  MostrarCambios(Archivo a, char * version){
    return NO_IMPLEMENTADA;
}

//Chequear si dos versiones son iguales.
TipoRet Iguales(Archivo a, char * version1, char * version2,  bool &iguales){
    return NO_IMPLEMENTADA;
}

//Operación Opcional:
//Crea una versión independiente de otras existentes.
TipoRet  VersionIndependiente(Archivo &a, char * version){
    return NO_IMPLEMENTADA;
}


