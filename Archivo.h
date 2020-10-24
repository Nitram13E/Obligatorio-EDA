#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

enum _retorno{
	OK, ERROR, NO_IMPLEMENTADA
};

typedef enum _retorno TipoRet;

typedef struct Linea
{
	char * contlinea;
	int indice;
	struct Linea * next;
	
}*linea;

typedef struct Version
{
	char * num_version;
	linea contenido;
	struct Version * siguiente;
	struct Version * subVersion;
	
}*numVersion;

typedef struct _archivo
{
	char * nombre;

	numVersion versiones;
	
}*Archivo;



Archivo CrearArchivo(char * nombre);

TipoRet BorrarArchivo(Archivo &a);

TipoRet CrearVersion(Archivo &a, char * version, char * &error);

TipoRet BorrarVersion(Archivo &a, char * version);

TipoRet MostrarVersiones(Archivo a);

TipoRet  InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * error);

TipoRet  BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error);

TipoRet  MostrarTexto(Archivo a, char * version);

TipoRet  MostrarCambios(Archivo a, char * version);

TipoRet Iguales(Archivo a, char * version1, char * version2,  bool &iguales);

TipoRet  VersionIndependiente(Archivo &a, char * version);


#endif // ARCHIVO2_H_INCLUDED
