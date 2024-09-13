/*
DESCRIPCION: Programa que muestra por pantalla la imagen de su propio proceso
en memoria virtual (PCB+Codigo+Datos+Stack). Se mostraran solo aquellos campos
del PCB que sean brindados de acuerdo a la version del archivo cabecera
procfs.h y a la version del /proc disponible en este sistema operativo.

AUTOR: Martín Alejandro Fernandez - Ingenieria en Computacion - UNT-FACET
*/

#include <iostream>
#include "procfs.h"

using namespace std;
int main()
{
	system("clear");
	cout << " >>> IMAGEN DE UN PROCESO EN MEMORIA <<< " << endl;
	pcb();
	addr_proceso_mv();
	return 0;
}
