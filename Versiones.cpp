#include <stdlib.h>
#include <stdio.h>
#include "string.h"

#include "Archivo.h"
#include "Versiones.h"
#include "ControlStr.h"
#include "Lineas.h"

TipoRet CrearVersion(Archivo &a, char * version, char * error)
{
    if (a == NULL)
    {
        strcpy(error, "no existe archivo");
        return ERROR;
    }

    numVersion header_version = a -> versiones;
    
    if (a -> versiones == NULL)
    {
        if (strcmp(version,"1") == 0)
        {
            a -> versiones = defVersion(version,NULL,NULL,NULL);

            strcpy(error, "version creada");
            
            return OK;
        }

        strcpy(error,"La primera version debe de ser la 1");
        return ERROR;
    }

    //Versiones main: 1, 2, 3,...n
    if (typeVersion(version))
    {
        if (siguienteVersion(a -> versiones, version, NULL))
        {
            strcpy(error, "version creada");
            return OK;
        }
        
        strcpy(error, "No existe version anteriror");
        return ERROR;
    }

    //Sub Versiones
    numVersion padre = buscarPadre(a -> versiones, version);

    if (padre != NULL) //En caso de que el padre exista
    {
        if (padre -> subVersion != NULL)
        {
        //Si el padre ya tiene subVersion,
        //Quiere decir que la sub version a insertar tiene hermanos
        //Es por ello que la insertamos como siguiente al ultimo hermano

            if (siguienteVersion(padre -> subVersion, version, padre -> num_version)
)
            {
                strcpy(error, "version creada");
                return OK;
            }

            strcpy(error, "No existe version anterior");
            return ERROR;
        }

        //Si el padre no tiene sub version, significa que la version a crear sera la primera.
        if (version[strlen(version) - 1] == '1')
        {
            padre -> subVersion = defVersion(version,NULL,NULL,NULL);
            
            heredarTexto(padre, padre -> subVersion);
            
            strcpy(error, "subversion creada");
            return OK;
        }

        strcpy(error, "La primera primera subversion debe de ser 1");
        return ERROR;
    }

    // si padre == NULL
    strcpy(error, "Ha ocurrido un error");
    return ERROR;
}

TipoRet BorrarVersion(Archivo &a, char * version)
{
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

    	reasignarVersiones(toDelete -> siguiente, padre -> num_version, false);
    	borrarSubVersiones(toDelete);
    }

    return OK;
}

TipoRet MostrarVersiones(Archivo a)
{
    imprimirVersiones(a -> versiones, 0);

    return OK;
}

int contTab(char * num_version)
{
    int tab = 1;

    for (int c = 0; c < strlen(num_version); c++)
    {
        if (num_version[c] == '.')
        {
            tab++;
        }
    }

    return tab;
}

void imprimirVersiones(numVersion version, int tab)
{
    if (version == NULL)

        return;

    tab = contTab(version -> num_version);
    
    for (int i = 0; i < tab; i++)
    {
        printf("\t");
    }
    
    printf("%s\n", version -> num_version);
    
    imprimirVersiones(version -> subVersion, tab);

    imprimirVersiones(version -> siguiente, tab);
}


// Devuelve la version buscada.
numVersion buscarVersion(numVersion version, char * version_num)
{
    numVersion toFind = NULL;

    buscadorVersion(version, version_num, toFind);

    return toFind;
}

// Busca a la version.
void buscadorVersion(numVersion version, char * version_num, numVersion &toFind)
{
    if (version == NULL)
    return;

    if (strcmp(version -> num_version, version_num) == 0)
    {
        toFind = version;
    }

    buscadorVersion(version->subVersion, version_num, toFind);

    buscadorVersion(version -> siguiente, version_num, toFind);
}

numVersion buscarPadre(numVersion version, char * version_num)
{
	int child_length = 0; 
	int i = strlen(version_num) - 1;
	
	while (version_num[i] != '.')
	{
		child_length++, i--;
	}
	
	child_length = strlen(version_num) - (child_length + 1);
	
	char * auxPadre = new char[child_length];

	for (int i = 0; i < child_length; i++)
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
    nuevaVersion -> num_version = new char[80];
    
    nuevaVersion -> num_version = version;
    nuevaVersion -> siguiente = siguiente;
    nuevaVersion -> anterior = anterior;
    nuevaVersion -> subVersion = subVersion;
    nuevaVersion -> cambio = NULL;

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

int lastToNumber(char * version)
{
	int dot = 0, i = 0;
	char * number = new char[strlen(version)];
	
	for (int i = 0; i < strlen(version); i += 1)
	{
		if (version[i] == '.')
		{
			dot = i+1;
		}
	}
	
	while (version[dot] != '\0')
	{
		number[i] = version[dot];
		dot++, i++;
	}
	
	return atoi(number);
}

//Se inserta una nueva sub version como siguiente del ultimo hermano
bool siguienteVersion(numVersion &header_version, char * version, char * version_padre)
{
    numVersion iterador = header_version;
    numVersion nuevaVersion = NULL;

    while (iterador->siguiente != NULL && strcmp(iterador -> siguiente -> num_version, version) != 0)
    {
        iterador = iterador -> siguiente;
    }

    if (iterador -> siguiente != NULL)
    {
        reasignarVersiones(iterador -> siguiente, version_padre, true);
        nuevaVersion = defVersion(version, iterador -> siguiente, iterador, NULL);
        iterador -> siguiente -> anterior = nuevaVersion;
        iterador -> siguiente = nuevaVersion;

        heredarTexto(header_version, nuevaVersion);

        return true;
    }
    else if(version[strlen(version) - 1] == '1')
    {
        reasignarVersiones(header_version, version_padre, true);
        nuevaVersion = defVersion(version, header_version, NULL, NULL);
        header_version -> anterior = nuevaVersion;
        header_version = nuevaVersion;

        heredarTexto(header_version, nuevaVersion);

        return true;
    }
    else
    {
        int lastCharNode = lastToNumber(iterador -> num_version);
        int lastCharVersion = lastToNumber(version);

        if (lastCharVersion - lastCharNode == 1)
        {
            iterador -> siguiente = defVersion(version,NULL,iterador, NULL);

            heredarTexto(header_version, iterador -> siguiente);

            return true;
        }
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

void reasignarVersiones(numVersion &version, char * str_padre, bool signo)
{
    if (version == NULL) return;

    char * num_version = version -> num_version;

    reasignador(str_padre, version -> num_version, signo);

    reasignarVersiones(version -> siguiente, str_padre, signo);
    reasignarVersiones(version -> subVersion, str_padre, signo);
}

//esta funcion modifica el numero de la version a reaisgnar incrementandolo o decrementandolo
char *  reasignarVersion(char * toModify, char * &swapArray, bool suma_resta)
{
    int numero = atoi(toModify);

    if(suma_resta)
    {
        numero += 1;
    }
    else
    {
        numero -= 1;
    }
    
    sprintf(swapArray, "%d", numero);
}