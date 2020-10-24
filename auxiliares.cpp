#include "auxiliares.h"
#include <stdlib.h>

numVersion buscarVersion(numVersion versiones, char * version)
{

    if (versiones -> num_version == version)
    {
        return versiones;
    }

    return NULL;

}