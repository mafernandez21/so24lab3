/*
DESCRIPCION: Programa que muesta como un proceso en ejecución finaliza normalmente.

AUTOR: Martín Alejandro Fernandez - Ingenieria en Computacion - UNT-FACET
*/

#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

void f1(), f2(), f3();

int main()
{
    /*
    atexit(f1);
    atexit(f2);
    atexit(f3);
    */
    cout << "Preparandose para terminar" << endl;
    exit(0);
}

void f1()
{
    cout << "Ejecutando F1" << endl;
}

void f2()
{
    cout << "Ejecutando F2" << endl;
}

void f3()
{
    cout << "Ejecutando F3" << endl;
}
