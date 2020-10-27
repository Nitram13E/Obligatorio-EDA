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
            a -> versiones = defVersion(version);

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

            char * auxPadre = new char[strlen(version) - 2];

            for (int i = 0; i < strlen(version)-2; i++)
            {
                auxPadre[i] = version[i];
            }
            //lo que se hace en aux padre es buscar al padre de la subversion a crear
            //Por ejemplo: si la subversion es 1.1.1, auxPadre = 1.1
            //Este valor se utilizara en buscarPadre

            numVersion padre = buscarPadre(a->versiones, auxPadre);


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
                    if (version[0] == '1')
                    {
                        padre -> subVersion = defVersion(version);

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
    return NO_IMPLEMENTADA;
}

TipoRet MostrarVersiones(Archivo a){
    return NO_IMPLEMENTADA;
}

TipoRet  InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * &error){

    numVersion versionToInsert = buscarPadre(a -> versiones, version);

    if (versionToInsert != NULL && versionToInsert -> siguiente == NULL && versionToInsert->subVersion == NULL)
    {
        line headLine = versionToInsert->contenido;

        if (headLine == NULL)
        {
            versionToInsert -> contenido = defLinea(linea ,nroLinea);
        }
        else
        {
            line lineaAuxiliar = headLine;
            while (lineaAuxiliar -> siguiente != NULL)
            {
                lineaAuxiliar = lineaAuxiliar -> siguiente;
            }

            if ((lineaAuxiliar -> nroLinea) + 1 == nroLinea) {
              lineaAuxiliar -> siguiente = defLinea(linea, nroLinea);
            }
            else
            {

              error = "Las lineas deben ser creadas secuencialmente (uno a uno)";
              return ERROR;

            }

        }

        error = "Linea insertada";
        return OK;
    }
    else
    {
        error = "La version tiene subVersiones";
        return ERROR;
    }


    return NO_IMPLEMENTADA;
}

TipoRet  BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error){
    return NO_IMPLEMENTADA;
}

TipoRet  MostrarTexto(Archivo a, char * version){

    numVersion fileVersion = buscarPadre(a->versiones, version);

    line content = fileVersion->contenido;

    if (content == NULL)
    {
      printf("Version sin contenido\n");
    }
    else
    {

      while (content != NULL)
      {
          printf("%d \t %s\n", content->nroLinea, content->contLinea);
          content = content->siguiente;
      }

    }




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
