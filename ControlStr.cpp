#include "string.h"
#include "ControlStr.h"
#include "Versiones.h"

//esta funcion copia una cadena, desde una determinado posicion hacia un determinado caracter
void copiarCadena(char * toCopy, char * copier, int &char_position, char limit_char)
{
    int i = 0;
    int largo = strlen(toCopy);

    while(char_position != largo && toCopy[char_position] != limit_char)
    {
        copier[i] = toCopy[char_position];
        i++, char_position++;
    }
}

void reasignador(char * padre, char * &number, bool suma_resta)
{
    char * newArray  = new char[strlen(number) + 1]; // guarda el array resignado
    char * numberToModify = new char[strlen(number)]; // guarda la cadena con el numero a incrementar
    char * swapArray = new char[strlen(number)]; // array para utilizar en sprintf(resignarVersion) para hacer el cambio de int - string, ya que sprintf necesita un array limpio.
    char * CharactersAfterNumber = new char[strlen(number)];// guarda la cadena de caracteres posteriores al numero a modificar
    int i = 0, length_padre = 0;

    if(typeVersion(number))
    { // si lo que se quiere cambiar es una version main reasigna directamente al parametro number
        reasignarVersion(number, swapArray, suma_resta);

        //se le asigna el nuevo array a la version a reasignar
        strcpy(number, swapArray);
    }
    else
    {
        // subVersiones
        if(padre == NULL)
        {// si el padre es NULL significa que lo que se esta modificando es una version main
            length_padre = 0;

            //se copia la cadena hasta el primer punto
            copiarCadena(number, numberToModify, length_padre, '.');

            reasignarVersion(numberToModify, swapArray, suma_resta);

            //se lo concatena al nuevo array
            strcpy(newArray, swapArray);
            
            //se copia y concatena el resto de la cadena
            copiarCadena(number, CharactersAfterNumber, length_padre, '\0'); 
            strcat(newArray, CharactersAfterNumber);
            //se le asigna el nuevo array a la version a reasignar
            strcpy(number,newArray);
        }
        else
        {
            //de tener subversion padre, se le concatena el padre al nuevo array.
            length_padre = strlen(padre)+1;
            strcpy(newArray, padre);
            strcat(newArray, ".");

            //se copia la cadena desde la posicion del la version padre, analizando si el numero a modificar es lo ultimo o si tiene caracteres posteriores.
            while(number[length_padre] != '\0' && number[length_padre] != '.')
            {   
                numberToModify[i] = number[length_padre];
                i++, length_padre++;
            }

            // se reaisigna y concatena al nuevo array
            reasignarVersion(numberToModify, swapArray, suma_resta);
            strcat(newArray, swapArray);

            if(number[length_padre] != '\0')
            { //de tener puntos posteriores, estos se van a copiar y concatenar al nuevo array
                copiarCadena(number, CharactersAfterNumber, length_padre, '\0');
                strcat(newArray, CharactersAfterNumber);
            }

            //se le asigna el nuevo array a la version a reasignar
            strcpy(number,newArray);
        }
    }
}