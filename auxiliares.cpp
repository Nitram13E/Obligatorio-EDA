#include "auxiliares.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

numVersion defVersion(char * version)
{
    numVersion nuevaVersion = new struct Version;

    nuevaVersion -> num_version = version;
    nuevaVersion -> siguiente = NULL;
    nuevaVersion -> subVersion = NULL;

    return nuevaVersion;
}



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

void siguienteVersion(numVersion &header_version, char * version)
{
        while (header_version->siguiente != NULL)
        {
            header_version = header_version -> siguiente;
        }
        
        header_version -> siguiente = defVersion(version);
}