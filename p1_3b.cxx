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
int num1 = 5;
int num2;

int main()
{
	system("clear");
	cout << " >>> IMAGEN DE UN PROCESO EN MEMORIA <<< " << endl;
	pcb();
	addr_proceso_mv();
	int j;
	cout << "\nLa funcion main esta en  " << hex << ((int *)(main)) << endl;
	cout << "La funcion pcb() esta en  " << hex << ((int *)(pcb)) << endl;
	cout << "La funcion addr_proceso_mv() esta 	en  " << hex << ((int *)(addr_proceso_mv)) << endl;
	cout << "La variable num1 esta en  " << hex << ((int *)(&num1)) << endl;
	cout << "La variable num2 esta en  " << hex << ((int *)(&num2)) << endl;
	cout << "La variable j esta en  " << hex << ((int *)(&j)) << endl;
	return 0;
}
