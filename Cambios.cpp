#include <stdlib.h>
#include <stdio.h>
#include "string.h"

#include "Cambios.h"

cambio defCambio(bool tipo, unsigned int num_linea, char * linea)
{
    cambio newCambio = new struct Cambio;
    newCambio -> linea = new char[80];
    
    newCambio -> num_linea = num_linea;
    newCambio -> linea = linea;
    newCambio -> siguiente = NULL; 

    if (tipo)
    {
        newCambio -> tipo = "IL";
    }
    else
    {
        newCambio -> tipo = "BL";
    }

    return newCambio;
}

void agregarCambio(numVersion versionToInsert, bool tipo_cambio, char * linea, unsigned int nroLinea)
{
    cambio indexCambio = versionToInsert -> cambio;

    if (indexCambio != NULL)
    {
        while (indexCambio -> siguiente != NULL)
        {
            indexCambio = indexCambio -> siguiente;
        }

        indexCambio -> siguiente = defCambio(tipo_cambio, nroLinea, linea);
    }
    else
    {
        versionToInsert -> cambio = defCambio(tipo_cambio, nroLinea, linea);
    }
}

TipoRet MostrarCambios(Archivo a, char * version)
{
    numVersion fileVersion = buscarVersion(a -> versiones, version);

    if (fileVersion != NULL)
    {
        cambio indexCambio = fileVersion -> cambio;

        if (indexCambio != NULL)
        {
            printf("%s - %s\n", a -> nombre, fileVersion -> num_version);

            while (indexCambio != NULL)
            {
                printf("%s\t%i\t%s\n", indexCambio -> tipo, indexCambio -> num_linea, indexCambio -> linea);
                
                indexCambio = indexCambio -> siguiente;
            }
        }
        else
        {
            printf("No se realizaron modificaciones");
        }

        return OK;
    }

    return ERROR;
}