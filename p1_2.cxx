/*
DESCRIPCION: Programa que genera un arbol de procesos enumerando cada uno de
los procesos generados.

AUTOR: Martín Alejandro Fernandez - Ingenieria en Computacion - UNT-FACET
*/

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main()
{
	cout << "\n\nPROCESO INICIAL PID: " << getpid()
		 << "\tPPID: " << getppid() << "\n"
		 << endl;
	for (int i = 0; i < 3; ++i)
	{
		sleep(1);
		if (fork() == 0)
		{
			cout << "PROCESO HIJO\tPID: " << getpid()
				 << "\tPPID: " << getppid()
				 << "\tnaci con i= " << i
				 << endl;
		}
		else
		{
			cout << "PROCESO PADRE\tPID: " << getpid()
				 << "\the procreado con i= " << i
				 << endl;
		}
	}
	sleep(1);
	return 0;
}
