/*
DESCRIPCION: Programa que genera un proceso hijo y ambos muestran su
correspondiente PID y PPID utilizando las syscalls getpid()	y getppid().

AUTOR: Martín Alejandro Fernandez - Ingenieria en Computacion - UNT-FACET
*/

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main()
{
	pid_t pid_hijo; /*guardara el pid del hijo para que el padre lo muestre por pantalla*/
	if ((pid_hijo = fork()) != 0)
	{
		cout << "\n[PADRE]: Mi PID es " << getpid()
			 << " y mi padre es el proceso " << getppid()
			 << " he creado un proceso cuyo PID es " << pid_hijo
			 << endl;
		sleep(1);
	}
	else
	{
		cout << "\n[HIJO]: Mi PID es " << getpid()  // hijo muestra su pid
			 << " y mi padre es el proceso " << getppid() // hijo muestra el pid de su padre*/
			 << endl;
	}
	return 0;
}