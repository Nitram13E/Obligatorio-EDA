#include "auxiliares.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Veifica si la version ingresa existe
bool existeVersion(numVersion versiones, char * version)
{

    if (versiones != NULL)
    {

        if (versiones->num_version == version)
        {
            return true;
        }

        existeVersion(versiones -> siguiente, version);
        existeVersion(versiones -> subVersion, version);

    }


    return false;


}

// muestra versiones
void mostrarVersiones(numVersion version, int space)
{

    if (version == NULL)

      return;

   space += 2;

   mostrarVersiones(version->siguiente, space);

   for (int i = 2; i < space; i++){

       printf("   ");

   }


   printf("%s\n",version -> num_version);

   mostrarVersiones(version->subVersion, space);

}

// Busca al padre de la sub version a crear
numVersion buscarPadre(numVersion padre, char * padre_num)
{

    if (padre != NULL)
    {

        if (strcmp(padre->num_version, padre_num) == 0)
        {
            return padre;
        }


        if (padre->siguiente != NULL)
        {
            return buscarPadre(padre->siguiente, padre_num);
        }
        else if (padre -> subVersion != NULL)
        {
            return buscarPadre(padre->subVersion, padre_num);

        }

    }


    return NULL;
}

//Estructura para crear una nueva version
numVersion defVersion(char * version)
{
    numVersion nuevaVersion = new struct Version;

    nuevaVersion -> num_version = version;
    nuevaVersion -> siguiente = NULL;
    nuevaVersion -> subVersion = NULL;

    return nuevaVersion;
}


//Devuelve si la version ingresada es main o sub version
bool typeVersion(char * version)
{

    for (int i = 0; i < strlen(version); i++)
    {
        if (version[i] == '.')
        {
            return false;
        }

    }

    return true;

}

//Se inserta una nueva sub version como siguiente del ultimo hermano
bool siguienteVersion(numVersion &header_version, char * version)
{
        numVersion auxiliar = header_version;

        while (auxiliar->siguiente != NULL)
        {
            auxiliar = auxiliar -> siguiente;
        }

        int lastCharNode = auxiliar -> num_version[strlen(auxiliar -> num_version) - 1];
        int lastCharVersion = version[strlen(version) - 1];

        if (lastCharVersion - lastCharNode == 1)
        {
            auxiliar -> siguiente = defVersion(version);
            return true;
        }

        return false;
}


line defLinea(char * contLinea, int nroLinea, line siguienteLinea)
{

    line nuevaLinea = new struct Linea;
    nuevaLinea ->contLinea = contLinea;
    nuevaLinea -> nroLinea = nroLinea;
    nuevaLinea -> siguiente = siguienteLinea;

    return nuevaLinea;

}

void correrLineas(line &linea)
{
	if (linea == NULL) return;
	
	linea -> nroLinea += 1;
	
	correrLineas(linea -> siguiente); 
	
}


