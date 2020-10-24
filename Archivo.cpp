#include <stdlib.h>
#include "Archivo.h"
#include "auxiliares.cpp"
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

    if (a->versiones == NULL)
    {
        numVersion nuevaVersion = new struct Version;
        nuevaVersion -> num_version = version;
        nuevaVersion -> siguiente = NULL;
        nuevaVersion -> subVersion = NULL;
        a -> versiones = nuevaVersion;

        error = "version creada";
        return OK;

    } 
    else
    {
        if (buscarVersion(a -> versiones, version) == NULL)
        {
            return OK;
        } 
        else
        {
            return ERROR;
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



