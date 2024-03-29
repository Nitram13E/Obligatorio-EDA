#include <cstdlib>
#include <iostream>
#include <stdio.h>

#include "Archivo.h"
#include "Constantes.h"

using namespace std;



void menu();
void imprimirResultado(TipoRet retorno,Cadena error);
void leerLinea(Cadena linea);

int main()
{
    Archivo archivo = NULL;
    int numOper = 0;
    bool salir = false;
    TipoRet retorno = NO_IMPLEMENTADA;
    char opcion = 'n';
    Cadena cadenaAux = NULL;
    Cadena linea = NULL;
    Cadena version = NULL;
    Cadena error = NULL;
    Posicion nroLinea;
    do {
        menu();
        cin >> numOper;
        switch (numOper){
            case 1:
                  cout << "Ingrese nombre del archivo a crear: ";
                  cadenaAux = new char [MAX_LARGO_LINEA];
                 // fflush(stdin);
                  cin >> cadenaAux;
                  archivo=CrearArchivo(cadenaAux);
                  delete cadenaAux;
                  break;
           case 2:
                  cout << "Se va a borrar el archivo: ";
                  retorno = BorrarArchivo(archivo );
                  imprimirResultado(retorno);
                  break;
           case 5:
                  linea = new char [MAX_LARGO_LINEA];
                  version = new char [MAX_LARGO_LINEA];
                  error = new char [MAX_LARGO_LINEA];
                  cout << "Ingrese el numero de linea a insertar (debe ser >= 1 y <= cant lineas): ";
                  //fflush(stdout);
                  cin >>  nroLinea;
                  cout << "Ingrese la linea a insertar: ";
                  leerLinea(linea);
                  cout << "Ingrese version a modificar: ";
                  leerLinea(version);

                  retorno = InsertarLinea(archivo, version, linea, nroLinea, error);
                  imprimirResultado(retorno, error);

                  delete linea;
                  delete version;
                  delete error;
                  break;
           case 11:
                  cout << "Esta seguro de que desea salir (s/n)?: ";
                  cin >> opcion;
                  if (opcion == 's' || opcion == 'S'){
                     cout << "Saliendo...\n";
                     salir = true;
                  }
                  break;
           default:
                   cout << numOper<<"No ingreso una opcion valida, vuelva a intentarlo...\n";
                   //getchar();

        }
        cout << "\n";
        cout << "Presione Enter Para continuar\n";
        getchar();
        system("clear");
    } while (!salir);
    return 0;
}

void menu(){
    cout << "Estructuras de Datos y Algoritmos - Obligatorio 1\n";
    cout << "Manejador de versiones\n\n";
    cout << "Lista de operaciones disponibles:\n";
    cout << "1)  CrearArchivo\n";
    cout << "2)  BorrarArchivo\n";
    cout << "3)  CrearVersion\n";
    cout << "4)  MostrarVersiones\n";
    cout << "5)  InsertarLinea\n";
    cout << "6)  BorrarLinea\n";
    cout << "7)  MostrarTexto\n";
    cout << "8)  MostrarCambios\n";
    cout << "9)  Iguales\n";
    cout << "10) VersionIndependiente\n";
    cout << "11) Salir\n\n";
    cout << "Ingrese el numero de la operacion a realizar: ";
}

void imprimirResultado(TipoRet retorno, Cadena error) {
     switch(retorno){
        case OK:
             cout << "Resultado: " << "OK" << endl;
             break;
        case ERROR:
             cout << "Resultado: " << "ERROR :" << error <<endl;
             break;
        case NO_IMPLEMENTADA:
             cout << "Resultado: " << "NO_IMPLEMENTADA"<< endl;
             break;
     }
}

void imprimirError(Cadena error) {
     cout << error << endl;
}

void leerLinea(Cadena linea){
    fflush(stdin);
    cin.getline(linea, MAX_LARGO_LINEA);

    printf("resultado:'%s'",linea);
}
