#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cstring>

#include "Archivo.h"
#include "Constantes.h"
#include "Versiones.h"
#include "Lineas.h"
#include "Cambios.h"

using namespace std;

void imprimirResultado(TipoRet retorno,Cadena error);

int main()
{
     Archivo archivo = NULL;
     TipoRet retorno = NO_IMPLEMENTADA;
     char * nombreArch;
     char * linea;
     char * version;
     char * version2;
     Cadena error = new char[MAX_LARGO_LINEA];
     Posicion nroLinea;
     bool iguales;

     // Creacion y eliminacion de archivo
     
     nombreArch = "archivo.txt";
     archivo = CrearArchivo(nombreArch);
     printf("El nombre del archivo es %s\n", archivo -> nombre);

     retorno = BorrarArchivo(archivo);
     imprimirResultado(retorno, error);

     nombreArch = "archivo.txt";
     archivo = CrearArchivo(nombreArch);
     printf("El nombre del archivo es %s\n", archivo -> nombre);
     
     // Creacion de versiones principales
     version = "1";
     printf("La version es igual a %s\n", version);
     retorno = CrearVersion(archivo, version, error);
     imprimirResultado(retorno, error);

     version = "2";
     printf("La version es igual a %s\n", version);
     retorno = CrearVersion(archivo, version, error);
     imprimirResultado(retorno, error);

     version = "3";
     printf("La version es igual a %s\n", version);
     retorno = CrearVersion(archivo,version, error);
     imprimirResultado(retorno, error);

     // Creacion de version principal erronea
     version = "7";
     printf("La version es igual a %s\n", version);
     retorno = CrearVersion(archivo,version, error);
     imprimirResultado(retorno, error);
     
     // Creacion de subversiones

     version = "1.1";
     printf("La version es igual a %s\n", version);
     retorno = CrearVersion(archivo,version, error);
     imprimirResultado(retorno, error);
     
     version = "1.1.1";
     printf("La version es igual a %s\n", version);
     retorno = CrearVersion(archivo,version, error);
     imprimirResultado(retorno, error);

     version = "2.1";
     printf("La version es igual a %s\n", version);
     retorno = CrearVersion(archivo,version, error);
     imprimirResultado(retorno, error);
     
     version = "2.1.1";
     printf("La version es igual a %s\n", version);
     retorno = CrearVersion(archivo,version, error);
     imprimirResultado(retorno, error);

     // Impresion de versiones

     MostrarVersiones(archivo);


     // Creacion de lineas de texto

     linea = "esta es la linea 1";
     nroLinea = 1;

     // Creacion de una linea de texto erronea
     version = "1";
     printf("Linea a agregar: %s\n", linea);
     retorno = InsertarLinea(archivo, version, linea, nroLinea, error);
     imprimirResultado(retorno, error);

     // Creacion de una linea de texto erronea
     version = "1.1";
     printf("Linea a agregar: %s\n", linea);
     retorno = InsertarLinea(archivo, version, linea, nroLinea, error);
     imprimirResultado(retorno, error);

     // Creacion de una linea de texto exitosa
     version = "1.1.1";
     printf("Linea a agregar: %s\n", linea);
     retorno = InsertarLinea(archivo, version, linea, nroLinea, error);
     imprimirResultado(retorno, error);

     // Agregar una nueva linea
     nroLinea = 2;
     linea = "esta es la linea 2";
     retorno = InsertarLinea(archivo, version, linea, nroLinea, error);
     printf("Linea a agregar: %s\n", linea);
     imprimirResultado(retorno, error);
     
     // Remplazar linea 1 por nueva linea
     linea = "esta es la nueva linea 1";
     nroLinea = 1;

     retorno = InsertarLinea(archivo, version, linea, nroLinea, error);
     printf("Linea a agregar: %s\n", linea);
     imprimirResultado(retorno, error);
     
     // Eliminacion de una linea de version 1.1.1
     
     nroLinea = 2;

     retorno = BorrarLinea(archivo, version, nroLinea, error);
     imprimirResultado(retorno, error);

     // Mostrar lineas de la version 1.1.1

     MostrarTexto(archivo, version);

     // Mostrar los cambios realizados a la version 1.1.1

     MostrarCambios(archivo, version);

     //Comparar si dos versiones son iguales - Caso falso
     
     version = "1.1";
     version2 = "1";

     retorno = Iguales(archivo, version2, version, iguales);
     cout << "resultado: " << iguales << endl;

     // Comparar si dos versiones son iguales - Caso verdadero

     // Creacion de la version que hereda el mismo contenido que su padre
     version = "1.1.1.1";
     retorno = CrearVersion(archivo, version, error);
     imprimirResultado(retorno, error);

     // Comparacion entre version padre y version descendiente

     version2 = "1.1.1";
     retorno = Iguales(archivo, version2, version, iguales);
     cout << "resultado: " << iguales << endl;
     

     return 0;
}


void imprimirResultado(TipoRet retorno, Cadena error)
{
     switch(retorno)
     {
        case OK:
             cout << "OK: " << error << endl;
             break;
        case ERROR:
             cout << "ERROR: " << error <<endl;
             //free(error);
             break;
        case NO_IMPLEMENTADA:
             cout << "NO_IMPLEMENTADA"<< endl;
             break;
     }
}