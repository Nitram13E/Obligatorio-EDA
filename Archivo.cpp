#include <stdlib.h>
#include <stdio.h>
#include "Archivo.h"
#include "auxiliares.cpp"
#include "string.h"


Archivo CrearArchivo(char * nombre){
    
    Archivo nuevoArchivo = new struct _archivo;
    nuevoArchivo -> nombre = nombre;
    nuevoArchivo -> versiones = NULL;

    return nuevoArchivo;
}

TipoRet BorrarArchivo(Archivo &a){
    return NO_IMPLEMENTADA;
}

TipoRet CrearVersion(Archivo &a, char * version, char * &error){

    numVersion aux = a -> versiones;
    char dot = ' ';
    int length = strlen(version);


    if (a->versiones == NULL)
    {
        a -> versiones = defVersion(version);

        error = "version creada";
        return OK;

    }
    else
    {
        if (typeVersion(version))
        {

            while (aux->siguiente != NULL)
            {
                aux = aux -> siguiente;
            }
            
            aux -> siguiente = defVersion(version);

            error = "version creada";
            return OK;
            
        }
        else
        {

            char * auxPadre = new char[strlen(version) - 2];

            for (int i = 0; i < strlen(version)-2; i++)
            {
                auxPadre[i] = version[i];
            }

            numVersion padre = buscarPadre(a->versiones, auxPadre);

            padre -> subVersion = defVersion(version);
            
            return OK;

        }
        
        
        
    }

    return NO_IMPLEMENTADA;
}

TipoRet BorrarVersion(Archivo &a, char * version){
    return NO_IMPLEMENTADA;
}

TipoRet MostrarVersiones(Archivo a){
    return NO_IMPLEMENTADA;
}

TipoRet  InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * error){
    return NO_IMPLEMENTADA;
}

TipoRet  BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error){
    return NO_IMPLEMENTADA;
}

TipoRet  MostrarTexto(Archivo a, char * version){
    return NO_IMPLEMENTADA; 
}

TipoRet  MostrarCambios(Archivo a, char * version){
    return NO_IMPLEMENTADA;
}

TipoRet Iguales(Archivo a, char * version1, char * version2,  bool &iguales){
    return NO_IMPLEMENTADA;
}

TipoRet  VersionIndependiente(Archivo &a, char * version){
    return NO_IMPLEMENTADA;
}



