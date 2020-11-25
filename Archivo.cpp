#include <stdlib.h>
#include <stdio.h>
#include "string.h"

#include "Archivo.h"
#include "Versiones.h"

Archivo CrearArchivo(char * nombre)
{
    Archivo nuevoArchivo = new struct _archivo;
    nuevoArchivo -> nombre = new char[80];

    nuevoArchivo -> nombre = nombre;
    nuevoArchivo -> versiones = NULL;

    return nuevoArchivo;
}

TipoRet BorrarArchivo(Archivo &a)
{
    if (a == NULL)
    {
        return ERROR;
    }

    borrarVersiones(a -> versiones);
    delete a -> nombre;
    a = NULL;

    return OK;
}