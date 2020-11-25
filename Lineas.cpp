#include <stdlib.h>
#include <stdio.h>
#include "string.h"

#include "Lineas.h"
#include "Versiones.h"
#include "Cambios.h"

line defLinea(char * contLinea, int nroLinea, line siguienteLinea)
{
    line nuevaLinea = new struct Linea;
    nuevaLinea -> contLinea = new char[80];
    
    nuevaLinea -> contLinea = contLinea;
    nuevaLinea -> nroLinea = nroLinea;
    nuevaLinea -> siguiente = siguienteLinea;

    return nuevaLinea;
}
TipoRet  InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * error)
{
    if (a == NULL)
    {
        strcpy(error, "Archivo vacio");
        return ERROR;
    }
    
    numVersion versionToInsert = buscarVersion(a -> versiones, version);

    if (versionToInsert != NULL && versionToInsert->subVersion == NULL)
    {
        line headLine = versionToInsert->contenido;

        if (headLine == NULL)
        {
            versionToInsert -> contenido = defLinea(linea ,nroLinea, NULL);
        }
        else
        {
            line lineaIteradora = headLine;
            
            	if (headLine -> nroLinea != nroLinea)
            	{
            		while (lineaIteradora -> siguiente != NULL && lineaIteradora -> siguiente -> nroLinea != nroLinea)
           			{
                	    lineaIteradora = lineaIteradora -> siguiente;
            		}
            	}

				if (headLine -> nroLinea == nroLinea)
           		{
           			correrLineas(lineaIteradora, true);
		  			versionToInsert -> contenido = defLinea(linea,nroLinea, lineaIteradora);
           		}
           		else if (lineaIteradora -> siguiente != NULL)
           		{
           			correrLineas(lineaIteradora -> siguiente, true);
            	}
				else if ((lineaIteradora -> nroLinea) + 1 == nroLinea)
            	{
              	    lineaIteradora -> siguiente = defLinea(linea, nroLinea, NULL);
            	}
            	else
            	{
              	    strcpy(error, "Las lineas deben ser creadas secuencialmente (uno a uno)");
              	    return ERROR;
            	}
        }

        strcpy(error, "Linea insertada");

        agregarCambio(versionToInsert, true, linea, nroLinea);

        return OK;
    }

    strcpy(error, "No se ha podido agregar la linea");
    return ERROR;
}

TipoRet  BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char *  error)
{    
    numVersion versionToInsert = buscarVersion(a -> versiones, version);

    if (versionToInsert != NULL && versionToInsert->subVersion == NULL)
    {
        line headLine = versionToInsert -> contenido;
        line toDelete = NULL;

        if (headLine != NULL)
        {

            if (nroLinea == headLine -> nroLinea)
            {
                correrLineas(headLine ->siguiente, false);
                versionToInsert->contenido = headLine -> siguiente;

                agregarCambio(versionToInsert, false, headLine -> contLinea, nroLinea);
                delete headLine;
            }
            else
            {
                while (headLine -> siguiente != NULL && headLine -> siguiente -> nroLinea != nroLinea)
                {
                    headLine = headLine -> siguiente;
                }

                toDelete = headLine -> siguiente;
                correrLineas(headLine -> siguiente, false);
                headLine -> siguiente = headLine -> siguiente -> siguiente;
                
                agregarCambio(versionToInsert, false, toDelete -> contLinea, nroLinea);
                delete toDelete;
            }

            strcpy(error, "linea eliminada.");
            
            return OK;
        }
        else
        {
            strcpy(error, "Version sin lineas");
            return ERROR;
        }
    }

    return ERROR;
}

TipoRet  MostrarTexto(Archivo a, char * version)
{
    numVersion fileVersion = buscarVersion(a -> versiones, version);

    if (fileVersion != NULL)
    {
        line content = fileVersion -> contenido;

        printf("%s - %s\n\n", a -> nombre, fileVersion -> num_version);

        if (content == NULL)
        {
            printf("Version sin contenido\n");
        }
        else
        {

            while (content != NULL)
            {
                printf("%d\t%s\n", content -> nroLinea, content -> contLinea);
                content = content -> siguiente;
            }
        }

        return OK;
    }
    
    return ERROR;
}

void correrLineas(line &linea, bool signo)
{
	if (linea == NULL) return;
	
    if (signo)
    {
        linea -> nroLinea += 1;
    }
    else
    {
        linea -> nroLinea -= 1;
    }
    
	correrLineas(linea -> siguiente, signo); 
}


TipoRet Iguales(Archivo a, char * version1, char * version2,  bool &iguales)
{
    numVersion version_1 = buscarVersion(a -> versiones, version1);
    numVersion version_2 = buscarVersion(a -> versiones, version2);

    line contentV1 = version_1 -> contenido;
    line contentV2 = version_2 -> contenido;

    if (contentV1 == NULL || contentV2 == NULL)
    {
        iguales = false;

        return ERROR;
    }
    else
    {
        iguales = true;
        
        while (iguales && contentV1 != NULL && contentV2 != NULL)
        {
            if (strcmp(contentV1 -> contLinea, contentV2 -> contLinea) != 0)
            {
                iguales = false;
            }
            
            contentV1 = contentV1 -> siguiente;
            contentV2 = contentV2 -> siguiente;
        }

        return OK;
    }
}
