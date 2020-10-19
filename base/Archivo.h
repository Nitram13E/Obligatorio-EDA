#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED



/*
    1) El manejador s�lo permitir� trabajar con un archivo de texto y sus diferentes versiones.
    2) Las versiones se identifican de manera un�voca por una secuencia de 1 o m�s n�meros separados por un punto. Estos n�meros pueden ser de m�s de 1 d�gito y no hay l�mite en la secuencia de n�meros. Las versiones nunca empiezan ni terminan con un punto. Algunos ejemplos son: 4, 2.3, 4.12.3.21, 1.2.3.4.5.6.7.8.9.10.11
    3) Cada versi�n puede tener 0, 1 � m�s subversiones dependientes.
    4) Una versi�n depende y tiene como padre una sola versi�n, excepto las versiones iniciales del archivo (correspondientes a los n�meros: 1, 2, 3�).
    5) Cada versi�n X de un archivo incorpora 0, 1 o m�s modificaciones a la versi�n padre (si existe) de X.
    6) En el sistema se distingue el uso de min�sculas y may�sculas. Por ejemplo CASA ? Casa ? casa.
    7) Solo se puede usar la librer�a stdio.h en el archivo cpp que contenga la funci�n main(). S�lo se puede utilizar para debug, nada m�s. Pero la entrega final no lo puede incluir.
    8) Los grupos son de 3 personas. S�lo puede caber la posibilidad de uno o dos grupos de 2 personas, en caso de que la cantidad de estudiantes no sea m�ltiplo de tres.
*/


enum _retorno{
	OK, ERROR, NO_IMPLEMENTADA
};

typedef enum _retorno TipoRet;

struct _archivo{
/* aqu� deben figurar los campos que usted considere necesarios para manipular el archivo con  sus versiones */
};
typedef _archivo* Archivo;



//Crear el archivo.
Archivo CrearArchivo(char * nombre);

/*
Crea el archivo con el nombre especificado y lo inicializa sin contenido (vac�o). El archivo creado es retornado.
Esta operaci�n se ejecuta al inicio de una sesi�n de trabajo con un archivo.
	*/

//Borrar el archivo.
TipoRet BorrarArchivo(Archivo &a);

/*Elimina toda la memoria utilizada por el archivo y asigna NULL al puntero a. Se asume como precondici�n que a referencia a un archivo (en particular a es distinto a NULL).
Esta operaci�n se ejecuta al final de una sesi�n de trabajo con un archivo.

Retornos posibles:
OK
Siempre retorna OK.
ERROR
No existen errores posibles.
NO_IMPLEMENTADA
Cuando a�n no se implement�. Es el tipo de retorno por defecto.
*/

//Operaciones Relativas a las Versiones:

//Crear una nueva versi�n.
TipoRet CrearVersion(Archivo &a, char * version, char * error);
/*Crea una nueva versi�n del archivo si la versi�n especificada cumple con las siguientes reglas:
    � El padre de la nueva versi�n a crear ya debe existir. Por ejemplo, si creo la versi�n 2.15.1, la versi�n 2.15 ya debe existir.
Las versiones del primer nivel no siguen esta regla, ya que no tienen versi�n padre.
    � No pueden quedar �huecos� entre versiones hermanas. Por ejemplo, si creamos la versi�n 2.15.3, las versiones 2.15.1 y 2.15.2 ya deben existir.*/

//Borrar una versi�n, junto con sus hijos (subversiones), liberando toda la memoria involucrada.
TipoRet BorrarVersion(Archivo &a, char * version);
/*Elimina una versi�n del archivo si la version pasada por par�metro existe. En otro caso la operaci�n quedar� sin efecto. Si la versi�n a eliminar posee subversiones, �stas deber�n ser eliminadas tambi�n, as� como el texto asociado a cada una de las versiones. El texto ser� explicado m�s adelante*/


//Mostrar todas las versiones de un archivo de forma jer�rquica.
TipoRet MostrarVersiones(Archivo a);
/*FORMATO: En primer lugar muestra el nombre del archivo. Despu�s de una l�nea en blanco lista todos las versiones del archivo ordenadas por nivel jer�rquico e indentadas seg�n muestra el siguiente ejemplo (cada nivel est� indentado por un tabulador). */


//Operaciones Relativas al Texto:

//Insertar una l�nea de texto, en cierta posici�n, a una versi�n de un archivo.
TipoRet  InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * error);
/*Esta funci�n inserta una linea de texto a la version par�metro en la posici�n nroLinea.
El n�mero de l�nea debe estar entre 1 y n+1, siendo n la cantidad de l�neas del archivo. Por ejemplo, si el texto tiene 7 l�neas, se podr� insertar en las posiciones 1 (al comienzo) a 8 (al final).
Si se inserta en un n�mero de l�nea existente, �sta y las siguientes l�neas se correr�n hacia adelante (abajo) dejando el espacio para la nueva l�nea.
No se puede insertar una l�nea en una versi�n que tenga subversiones.
Notar que el crear un archivo, �ste no es editable hasta que no se crea al menos una versi�n del mismo. S�lo las versiones de un archivo son editables (se pueden insertar o suprimir l�neas), siempre que no tengan subversiones creadas.
En caso que TipoRet sea ERROR, en error se debe cargar cu�l es el mismo.*/


//Borrar una l�nea de texto, en cierta posici�n, a una versi�n de un archivo.
TipoRet  BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error);
/*Esta funci�n elimina una l�nea de texto de la version del archivo a en la posici�n nroLinea.
El n�mero de l�nea debe estar entre 1 y n, siendo n la cantidad de l�neas del archivo. Por ejemplo, si el texto tiene 7 l�neas, se podr�n eliminar l�neas de las posiciones 1 a 7.
Cuando se elimina una l�nea, las siguientes l�neas se corren, decrementando en una unidad sus posiciones para ocupar el lugar de la l�nea borrada.
No se puede borrar una l�nea de una versi�n que tenga subversiones creadas.
En caso que TipoRet sea ERROR, en error se debe cargar cu�l es el mismo.*/


//Mostrar el texto completo de una versi�n.
TipoRet  MostrarTexto(Archivo a, char * version);
/*Esta funci�n muestra el texto completo de la version, teniendo en cuenta los cambios realizados en dicha versi�n y en las versiones ancestras, de la cual ella depende.

FORMATO: En primer lugar se muestra el nombre del archivo. Luego, separado por un gui�n se mostrar� la version. Despu�s de una l�nea en blanco lista todas las l�neas del texto. Cada l�nea comienza con el n�mero de l�nea y separado por un tabulador se mostrar� el texto.*/

//Mostrar todas las modificaciones en el texto de una versi�n X, respecto a la versi�n padre de X.
TipoRet  MostrarCambios(Archivo a, char * version);

/*Esta funci�n muestra los cambios que se realizaron en el texto de la version par�metro, sin incluir los cambios realizados en las versiones ancestras de la cual dicha versi�n depende.
FORMATO: En primer lugar muestra el nombre del archivo. Luego, separado por un gui�n se mostrar� la version. Despu�s de una l�nea en blanco lista todos los cambios realizados al texto. Cada cambio se muestra en una nueva l�nea. Si es una inserci�n comenzar� con IL y si es un borrado con BL. Luego separado por un tabulador se mostrar� el n�mero de la l�nea modificada y, s�lo en el caso de una inserci�n, luego de otro tabulador el texto insertado.
*/

//Chequear si dos versiones son iguales.
TipoRet Iguales(Archivo a, char * version1, char * version2,  bool &iguales);
/*Esta funci�n asigna al par�metro booleano (iguales) el valor true si ambas versiones (version1 y version2)
del archivo tienen exactamente el mismo texto, y false en caso contrario.*/


//Operaci�n Opcional:
//Crea una versi�n independiente de otras existentes.
TipoRet  VersionIndependiente(Archivo &a, char * version);
/*Esta funci�n crea una nueva versi�n al final del primer nivel con todos los cambios de la version especificada
y de sus versiones ancestras. La versi�n que se crea debe ser independiente de cualquier otra versi�n.
Por ejemplo, si creamos una versi�n independiente a partir de la 2.11.3, entonces se crea una nueva versi�n
al final del primer nivel (si existen las versiones 1, 2, 3 y 4, entonces se crea la 5) con los cambios realizados a las versiones 2, 2.11 y 2.11.3. */

#endif // ARCHIVO2_H_INCLUDED
