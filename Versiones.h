#include "Archivo.h"
#include "Lineas.h"

TipoRet CrearVersion(Archivo &a, char * version, char * error);

TipoRet BorrarVersion(Archivo &a, char * version);

TipoRet MostrarVersiones(Archivo a);

void imprimirVersiones(numVersion, int);

numVersion buscarVersion(numVersion, char *);

numVersion buscarPadre(numVersion, char *);

numVersion defVersion(char *, numVersion, numVersion, numVersion);

bool typeVersion(char *);

int lastToNumber(char *);

bool siguienteVersion(numVersion &, char * , char *);

void borrarVersiones(numVersion&);

void borrarSubVersiones(numVersion&);

void reasignarVersiones(numVersion &, char *, bool);

char *  reasignarVersion(char *, char *&, bool);
