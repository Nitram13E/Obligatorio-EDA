#include "Archivo.h"

void imprimirVersiones(numVersion, int);

numVersion buscarVersion(numVersion, char *);

numVersion buscarPadre(numVersion, char *);

numVersion defVersion(char *, numVersion, numVersion, numVersion);

bool typeVersion(char *);

int lastToNumber(char *);

bool siguienteVersion(numVersion&, char *);

void borrarVersiones(numVersion&);

void borrarSubVersiones(numVersion&);

void reasignarVersiones(numVersion&, int, bool);

cambio defCambio(bool, unsigned int, char*);

void agregarCambio(numVersion, bool, char*, unsigned int);

line defLinea(char*, int, line);

void correrLineas(line&, bool);

