#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED



/*
    1) El manejador sólo permitirá trabajar con un archivo de texto y sus diferentes versiones.
    2) Las versiones se identifican de manera unívoca por una secuencia de 1 o más números separados por un punto. Estos números pueden ser de más de 1 dígito y no hay límite en la secuencia de números. Las versiones nunca empiezan ni terminan con un punto. Algunos ejemplos son: 4, 2.3, 4.12.3.21, 1.2.3.4.5.6.7.8.9.10.11
    3) Cada versión puede tener 0, 1 ó más subversiones dependientes.
    4) Una versión depende y tiene como padre una sola versión, excepto las versiones iniciales del archivo (correspondientes a los números: 1, 2, 3…).
    5) Cada versión X de un archivo incorpora 0, 1 o más modificaciones a la versión padre (si existe) de X.
    6) En el sistema se distingue el uso de minúsculas y mayúsculas. Por ejemplo CASA ? Casa ? casa.
    7) Solo se puede usar la librería stdio.h en el archivo cpp que contenga la función main(). Sólo se puede utilizar para debug, nada más. Pero la entrega final no lo puede incluir.
    8) Los grupos son de 3 personas. Sólo puede caber la posibilidad de uno o dos grupos de 2 personas, en caso de que la cantidad de estudiantes no sea múltiplo de tres.
*/


enum _retorno{
	OK, ERROR, NO_IMPLEMENTADA
};

typedef enum _retorno TipoRet;

struct _archivo{
/* aquí deben figurar los campos que usted considere necesarios para manipular el archivo con  sus versiones */
};
typedef _archivo* Archivo;



//Crear el archivo.
Archivo CrearArchivo(char * nombre);

/*
Crea el archivo con el nombre especificado y lo inicializa sin contenido (vacío). El archivo creado es retornado.
Esta operación se ejecuta al inicio de una sesión de trabajo con un archivo.
	*/

//Borrar el archivo.
TipoRet BorrarArchivo(Archivo &a);

/*Elimina toda la memoria utilizada por el archivo y asigna NULL al puntero a. Se asume como precondición que a referencia a un archivo (en particular a es distinto a NULL).
Esta operación se ejecuta al final de una sesión de trabajo con un archivo.

Retornos posibles:
OK
Siempre retorna OK.
ERROR
No existen errores posibles.
NO_IMPLEMENTADA
Cuando aún no se implementó. Es el tipo de retorno por defecto.
*/

//Operaciones Relativas a las Versiones:

//Crear una nueva versión.
TipoRet CrearVersion(Archivo &a, char * version, char * error);
/*Crea una nueva versión del archivo si la versión especificada cumple con las siguientes reglas:
    • El padre de la nueva versión a crear ya debe existir. Por ejemplo, si creo la versión 2.15.1, la versión 2.15 ya debe existir.
Las versiones del primer nivel no siguen esta regla, ya que no tienen versión padre.
    • No pueden quedar “huecos” entre versiones hermanas. Por ejemplo, si creamos la versión 2.15.3, las versiones 2.15.1 y 2.15.2 ya deben existir.*/

//Borrar una versión, junto con sus hijos (subversiones), liberando toda la memoria involucrada.
TipoRet BorrarVersion(Archivo &a, char * version);
/*Elimina una versión del archivo si la version pasada por parámetro existe. En otro caso la operación quedará sin efecto. Si la versión a eliminar posee subversiones, éstas deberán ser eliminadas también, así como el texto asociado a cada una de las versiones. El texto será explicado más adelante*/


//Mostrar todas las versiones de un archivo de forma jerárquica.
TipoRet MostrarVersiones(Archivo a);
/*FORMATO: En primer lugar muestra el nombre del archivo. Después de una línea en blanco lista todos las versiones del archivo ordenadas por nivel jerárquico e indentadas según muestra el siguiente ejemplo (cada nivel está indentado por un tabulador). */


//Operaciones Relativas al Texto:

//Insertar una línea de texto, en cierta posición, a una versión de un archivo.
TipoRet  InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * error);
/*Esta función inserta una linea de texto a la version parámetro en la posición nroLinea.
El número de línea debe estar entre 1 y n+1, siendo n la cantidad de líneas del archivo. Por ejemplo, si el texto tiene 7 líneas, se podrá insertar en las posiciones 1 (al comienzo) a 8 (al final).
Si se inserta en un número de línea existente, ésta y las siguientes líneas se correrán hacia adelante (abajo) dejando el espacio para la nueva línea.
No se puede insertar una línea en una versión que tenga subversiones.
Notar que el crear un archivo, éste no es editable hasta que no se crea al menos una versión del mismo. Sólo las versiones de un archivo son editables (se pueden insertar o suprimir líneas), siempre que no tengan subversiones creadas.
En caso que TipoRet sea ERROR, en error se debe cargar cuál es el mismo.*/


//Borrar una línea de texto, en cierta posición, a una versión de un archivo.
TipoRet  BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error);
/*Esta función elimina una línea de texto de la version del archivo a en la posición nroLinea.
El número de línea debe estar entre 1 y n, siendo n la cantidad de líneas del archivo. Por ejemplo, si el texto tiene 7 líneas, se podrán eliminar líneas de las posiciones 1 a 7.
Cuando se elimina una línea, las siguientes líneas se corren, decrementando en una unidad sus posiciones para ocupar el lugar de la línea borrada.
No se puede borrar una línea de una versión que tenga subversiones creadas.
En caso que TipoRet sea ERROR, en error se debe cargar cuál es el mismo.*/


//Mostrar el texto completo de una versión.
TipoRet  MostrarTexto(Archivo a, char * version);
/*Esta función muestra el texto completo de la version, teniendo en cuenta los cambios realizados en dicha versión y en las versiones ancestras, de la cual ella depende.

FORMATO: En primer lugar se muestra el nombre del archivo. Luego, separado por un guión se mostrará la version. Después de una línea en blanco lista todas las líneas del texto. Cada línea comienza con el número de línea y separado por un tabulador se mostrará el texto.*/

//Mostrar todas las modificaciones en el texto de una versión X, respecto a la versión padre de X.
TipoRet  MostrarCambios(Archivo a, char * version);

/*Esta función muestra los cambios que se realizaron en el texto de la version parámetro, sin incluir los cambios realizados en las versiones ancestras de la cual dicha versión depende.
FORMATO: En primer lugar muestra el nombre del archivo. Luego, separado por un guión se mostrará la version. Después de una línea en blanco lista todos los cambios realizados al texto. Cada cambio se muestra en una nueva línea. Si es una inserción comenzará con IL y si es un borrado con BL. Luego separado por un tabulador se mostrará el número de la línea modificada y, sólo en el caso de una inserción, luego de otro tabulador el texto insertado.
*/

//Chequear si dos versiones son iguales.
TipoRet Iguales(Archivo a, char * version1, char * version2,  bool &iguales);
/*Esta función asigna al parámetro booleano (iguales) el valor true si ambas versiones (version1 y version2)
del archivo tienen exactamente el mismo texto, y false en caso contrario.*/


//Operación Opcional:
//Crea una versión independiente de otras existentes.
TipoRet  VersionIndependiente(Archivo &a, char * version);
/*Esta función crea una nueva versión al final del primer nivel con todos los cambios de la version especificada
y de sus versiones ancestras. La versión que se crea debe ser independiente de cualquier otra versión.
Por ejemplo, si creamos una versión independiente a partir de la 2.11.3, entonces se crea una nueva versión
al final del primer nivel (si existen las versiones 1, 2, 3 y 4, entonces se crea la 5) con los cambios realizados a las versiones 2, 2.11 y 2.11.3. */

#endif // ARCHIVO2_H_INCLUDED
