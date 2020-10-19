#include<stdlib.h>
#include"Archivo.h"

/*
    1) El manejador s�lo permitir� trabajar con un archivo de texto y sus diferentes versiones.
    2) Las versiones se identifican de manera un�voca por una secuencia de 1 o m�s n�meros separados por un punto. Estos n�meros pueden ser de m�s de 1 d�gito y no hay l�mite en la secuencia de n�meros. Las versiones nunca empiezan ni terminan con un punto. Algunos ejemplos son: 4, 2.3, 4.12.3.21, 1.2.3.4.5.6.7.8.9.10.11
    3) Cada versi�n puede tener 0, 1 � m�s subversiones dependientes.
    4) Una versi�n depende y tiene como padre una sola versi�n, excepto las versiones iniciales del archivo (correspondientes a los n�meros: 1, 2, 3�).
    5) Cada versi�n X de un archivo incorpora 0, 1 o m�s modificaciones a la versi�n padre (si existe) de X.
    6) En el sistema se distingue el uso de min�sculas y may�sculas. Por ejemplo CASA ? Casa ? casa.
    7) Solo se puede usar la librer�a stdio.h en el archivo cpp que contenga la funci�n main(). S�lo se puede utilizar para debug, nada m�s. Pero la entrega final no lo puede incluir.
    8) Los grupos son de 3 personas. S�lo puede caber la posibilidad de uno o dos grupos de 2 personas, en caso de que la cantidad de estudiantes no sea m�ltiplo de tres.
*/



//Crear el archivo.
Archivo CrearArchivo(char * nombre){
    return NULL;
}

//Borrar el archivo.
TipoRet BorrarArchivo(Archivo &a){
    return NO_IMPLEMENTADA;
}

//Crear una nueva versi�n.
TipoRet CrearVersion(Archivo &a, char * version, char * error){
    return NO_IMPLEMENTADA;
}

//Borrar una versi�n, junto con sus hijos (subversiones), liberando toda la memoria involucrada.
TipoRet BorrarVersion(Archivo &a, char * version){
    return NO_IMPLEMENTADA;
}

//Mostrar todas las versiones de un archivo de forma jer�rquica.
TipoRet MostrarVersiones(Archivo a){
    return NO_IMPLEMENTADA;
}

//Operaciones Relativas al Texto:

//Insertar una l�nea de texto, en cierta posici�n, a una versi�n de un archivo.
TipoRet  InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * error){
    return NO_IMPLEMENTADA;
}

//Borrar una l�nea de texto, en cierta posici�n, a una versi�n de un archivo.
TipoRet  BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error){
    return NO_IMPLEMENTADA;
}

//Mostrar el texto completo de una versi�n.
TipoRet  MostrarTexto(Archivo a, char * version){
    return NO_IMPLEMENTADA;
}

//Mostrar todas las modificaciones en el texto de una versi�n X, respecto a la versi�n padre de X.
TipoRet  MostrarCambios(Archivo a, char * version){
    return NO_IMPLEMENTADA;
}

//Chequear si dos versiones son iguales.
TipoRet Iguales(Archivo a, char * version1, char * version2,  bool &iguales){
    return NO_IMPLEMENTADA;
}

//Operaci�n Opcional:
//Crea una versi�n independiente de otras existentes.
TipoRet  VersionIndependiente(Archivo &a, char * version){
    return NO_IMPLEMENTADA;
}


