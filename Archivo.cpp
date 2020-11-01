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

TipoRet BorrarArchivo(Archivo &a)
{
    borrarVersiones(a -> versiones);

    delete a -> nombre;
    delete a -> versiones;
    a = NULL;

    return OK;
}

TipoRet CrearVersion(Archivo &a, char * version, char * &error){

     if (a == NULL)
    {
        error = "no existe archivo";
        return ERROR;
    }

    numVersion header_version = a -> versiones;


    if (a->versiones == NULL)
    {
        if (version[0] == '1' && strlen(version) == 1)
        {
            a -> versiones = defVersion(version,NULL,NULL,NULL);

            error = "version creada";
            return OK;
        }
        else
        {
            error = "La primera version debe de ser la 1";
            return ERROR;
        }



    }
    else
    {
        //Versiones main: 1, 2, 3,...n
        if (typeVersion(version))
        {
            if (siguienteVersion(header_version, version))
            {
                error = "version creada";
                return OK;
            }
            else
            {
                error = "No existe version anteriror";
                return ERROR;
            }



        }
        else
        {
            //Sub Versiones

            numVersion padre = buscarPadre(a->versiones, version);


            if (padre != NULL) //En caso de que el padre exista
            {
                if(padre -> subVersion != NULL)
                {
                //Si el padre ya tiene subVersion,
                //Quiere decir que la sub version a insertar tien hermanos
                //Es por ello que la insertamos como siguiente al ultimo hermano
                  if (siguienteVersion(padre -> subVersion, version))
                  {
                      error = "version creada";
                      return OK;
                    }
                    else
                    {
                      error = "No existe version anteriror";
                      return ERROR;
                    }
                }
                else
                {
                 //Si el padre no tiene sub version, significa que la version a crear sera la primera.
                    if (version[strlen(version) - 1] == '1')
                    {
                        padre -> subVersion = defVersion(version,NULL,NULL,NULL);

                        error = "subversion creada";
                        return OK;
                    }
                    else
                    {
                        error = "La primera primera subversion debe de ser 1";
                        return ERROR;
                    }


                }

            }
            else // else padre == NULL
            {
                error = "Ha ocurrido un error";
                return ERROR;
            }

        }
    }

    return NO_IMPLEMENTADA;
}

TipoRet BorrarVersion(Archivo &a, char * version){

    numVersion toDelete = buscarVersion(a -> versiones, version);
    
    if (toDelete == NULL)
    {
        return ERROR;
    }
    
    toDelete -> anterior -> siguiente = toDelete -> siguiente;
    toDelete -> siguiente -> anterior = toDelete -> anterior;
    
    
    if (typeVersion(version))
    {
    	reasignarVersiones(toDelete -> siguiente, 0, false);
    	borrarVersiones(toDelete);
    }
    else
    {
    	numVersion padre = buscarPadre(a -> versiones, version);
    	reasignarVersiones(toDelete -> siguiente, strlen(padre -> num_version) + 1, false);	 
    	borrarSubVersiones(toDelete);
    }

    return OK;

}

TipoRet MostrarVersiones(Archivo a){

    imprimirVersiones(a -> versiones, 0);
    
    return OK;
}

TipoRet  InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * &error){

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
		  		    lineaIteradora -> siguiente = defLinea(linea, nroLinea, lineaIteradora -> siguiente);
            	}
				else if ((lineaIteradora -> nroLinea) + 1 == nroLinea)
            	{
              	    lineaIteradora -> siguiente = defLinea(linea, nroLinea, NULL);
            	}
            	else
            	{
              	    error = "Las lineas deben ser creadas secuencialmente (uno a uno)";
              	    return ERROR;
            	}            
        }

        error = "Linea insertada";

        //agregarCambio(versionToInsert, true, linea, nroLinea);

        return OK;
    }
    else
    {
        error = "La version tiene subVersiones";
        return ERROR;
    }


    return NO_IMPLEMENTADA;
}

TipoRet  BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char *  &error){
    
    numVersion versionToInsert = buscarVersion(a -> versiones, version);

    if(versionToInsert != NULL && versionToInsert -> siguiente == NULL && versionToInsert->subVersion == NULL)
    {
        line headLine = versionToInsert -> contenido;
        line toDelete = NULL;

        if(headLine != NULL)
        {
            if(nroLinea == headLine -> nroLinea)
            {
                correrLineas(headLine ->siguiente, false);
                versionToInsert->contenido = headLine -> siguiente;
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

                delete toDelete;
                
            }
            error = "linea %i eliminada.", nroLinea;
            return OK;
        }
        else
        {
            error = "Version sin lineas";
            return ERROR;
        }
        
    }
    
    return NO_IMPLEMENTADA;
}

TipoRet  MostrarTexto(Archivo a, char * version){

    numVersion fileVersion = buscarVersion(a->versiones, version);

    if(fileVersion != NULL)
    {
        line content = fileVersion->contenido;

        printf("%s - %s\n\n", a -> nombre, fileVersion -> num_version);

        if (content == NULL)
        {
            printf("Version sin contenido\n");
        }
        else
        {

            while (content != NULL)
            {
                printf("%d\t%s\n", content->nroLinea, content->contLinea);
                content = content->siguiente;
            }

        }

        return OK;
    }

    return ERROR;
}

TipoRet  MostrarCambios(Archivo a, char * version)
{
    numVersion fileVersion = buscarVersion(a -> versiones, version);

    if(fileVersion != NULL)
    {
        cambio indexCambio = fileVersion -> cambio;

        if(indexCambio != NULL)
        {
            while (indexCambio != NULL)
            {
                printf("MostrarCambios while");
                printf("%s\t%s\t%s", indexCambio -> tipo, indexCambio -> num_version, indexCambio -> linea);
                
                indexCambio = indexCambio -> siguiente;
            }
        }
        else
        {
            printf("No se realizaron modificaciones");
        }
        return OK;
    }
    else
    {
        return ERROR;
    }
    
    
}

TipoRet Iguales(Archivo a, char * version1, char * version2,  bool &iguales)
{
    numVersion version_1 = buscarVersion(a -> versiones, version1);
    numVersion version_2 = buscarVersion(a -> versiones, version2);

    line contentV1 = version_1 -> contenido;
    line contentV2 = version_2 -> contenido;

    if (contentV1 == NULL || contentV2 == NULL)
    {
        return ERROR;
    }
    else
    {
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

TipoRet  VersionIndependiente(Archivo &a, char * version){
    return NO_IMPLEMENTADA;
}
