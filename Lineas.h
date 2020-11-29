#include "Archivo.h"

TipoRet InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * error);

TipoRet BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error);

TipoRet MostrarTexto(Archivo a, char * version);

line defLinea(char*, int, line);

void correrLineas(line&, bool);

TipoRet Iguales(Archivo a, char * version1, char * version2,  bool &iguales);

void heredarTexto(numVersion, numVersion &);