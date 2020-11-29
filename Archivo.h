#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

enum _retorno{
	OK, ERROR, NO_IMPLEMENTADA
};

typedef enum _retorno TipoRet;

typedef struct Linea
{
	char * contLinea;
	int nroLinea;
	struct Linea * siguiente;

}*line;

typedef struct Cambio
{
	char * tipo;
	int num_linea;
	char * linea;
	struct Cambio * siguiente;

}*cambio;

typedef struct Version
{
	char * num_version;
	line contenido;
	struct Version * siguiente;
	struct Version * anterior;
	struct Version * subVersion;
	struct Cambio * cambio;

}*numVersion;

typedef struct _archivo
{
	char * nombre;
	numVersion versiones;

}*Archivo;


Archivo CrearArchivo(char * nombre);

TipoRet BorrarArchivo(Archivo &a);

#endif // ARCHIVO2_H_INCLUDED
