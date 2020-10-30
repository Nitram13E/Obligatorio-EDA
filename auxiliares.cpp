#include "auxiliares.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// muestra versiones
void imprimirVersiones(numVersion version, int tab)
{
    if (version == NULL)

        return;

    imprimirVersiones(version -> siguiente, tab);
    
    tab += 2;
    for (int i = 0; i < tab; i++)
    {
        printf("\t");
    }
    
    printf("%s\n", version -> num_version);
    
    
    imprimirVersiones(version -> subVersion, tab);
}

// Busca a la version.
numVersion buscarVersion(numVersion version, char * version_num)
{

    if (version != NULL)
    {

        if (strcmp(version->num_version, version_num) == 0)
        {
            return version;
        }


        if (version->siguiente != NULL)
        {
            return buscarVersion(version->siguiente, version_num);
        }
        else if (version -> subVersion != NULL)
        {
            return buscarVersion(version->subVersion, version_num);

        }

    }


    return NULL;
}


numVersion buscarPadre(numVersion version, char * version_num)
{
	char * auxPadre = new char[strlen(version_num) - 2];

	for (int i = 0; i < strlen(version_num)-2; i++)
	{
			auxPadre[i] = version_num[i];
	}
	//lo que se hace en aux padre es buscar al padre de la subversion a crear
	//Por ejemplo: si la subversion es 1.1.1, auxPadre = 1.1
	//Este valor se utilizara en buscarVersion.
	numVersion padre = buscarVersion(version, auxPadre);
	
	return padre;
}

//Estructura para crear una nueva version
numVersion defVersion(char * version, numVersion siguiente, numVersion anterior, numVersion subVersion)
{
    numVersion nuevaVersion = new struct Version;

    nuevaVersion -> num_version = version;
    nuevaVersion -> siguiente = siguiente;
    nuevaVersion -> anterior = anterior;
    nuevaVersion -> subVersion = subVersion;

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
            auxiliar -> siguiente = defVersion(version,NULL,auxiliar, NULL);
            return true;
        }

        return false;
}

void borrarVersiones(numVersion &version)
{
    if (version == NULL)
    {
        return;
    }

    if (!typeVersion(version -> num_version))
    {
       borrarVersiones(version -> siguiente);
    }

    borrarVersiones(version -> subVersion);

    if (typeVersion(version -> num_version))
    {
       delete version; 
    }
    else
    {
        delete version;
    }
}

void borrarSubVersiones(numVersion &version)
{
    if (version == NULL)
    {
        return;
    }

    borrarVersiones(version -> subVersion);

   	delete version;
    
}

void reasignarVersiones(numVersion &version, int posiciones_padre, bool signo)
{
	if (version == NULL) return;
	
   char * num_version = version -> num_version;

   if (posiciones_padre == 0)
   {
		 	if(signo)
		  {
		      num_version[0] ++;
		  }
		  else
		  {
		      num_version[0] --;
		  }  
   }
   else
   {
   		if(signo)
		  {
		      num_version[posiciones_padre] ++;
		  }
		  else
		  {
		      num_version[posiciones_padre] --;
		  }
   }
  
    
	reasignarVersiones(version -> siguiente, posiciones_padre, signo);
  reasignarVersiones(version -> subVersion, posiciones_padre, signo);
  
}








//Funciones para Linea


line defLinea(char * contLinea, int nroLinea, line siguienteLinea)
{

    line nuevaLinea = new struct Linea;
    nuevaLinea ->contLinea = contLinea;
    nuevaLinea -> nroLinea = nroLinea;
    nuevaLinea -> siguiente = siguienteLinea;

    return nuevaLinea;

}

void correrLineas(line &linea, bool signo)
{
	if (linea == NULL) return;
	
    if(signo)
    {
        linea -> nroLinea += 1;
    }
    else
    {
        linea -> nroLinea -= 1;
    }
    

	correrLineas(linea -> siguiente, signo); 
}


