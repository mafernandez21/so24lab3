/*	
DESCRIPCION: La librería contiene funciones que tienen como objetivo recuperar 
parte de la informacion brindada en el directorio /proc, en primera instancia 
para mostrar en pantalla la imagen de un proceso en memoria. 
La cantidad de informacion visible correspondiente al PCB de un proceso puede 
variar segun la version de este archivo y la version de /proc que se tenga 
para esta distribucion de linux.

AUTOR: Martín Alejandro Fernandez - Ingenieria en Computacion - UNT-FACET
*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include <string.h>

using namespace std;
const int bsize = 512; //Constante para definir el tamano del buffer de lectura.
extern int etext, edata, _end; /*Variables externas que guardan informacion 
sobre parte de la imagen del proceso en memoria virtual.*/

char * proc_lector(const char *str);/*Lee el contenido de un archivo determinado en 
/proc para un proceso en particular y lo almacena en un buffer.*/ 
int posicion(char *ptr, int cur);/*Obtiene una posicion determinada dentro 
del archivo almacenado en el buffer anterior.*/
void show_data(char *ptr, int pos);/*Muestra por pantalla el contenido de 
un campo de informacion dentro del archivo almacenado en el buffer.*/
void mostrar_comando(char *ptr);/*Muestra el comando que provoco la creacion 
del proceso en ejecucion (/proc/[PID]/cmdline).*/
void mostrar_pid(char *ptr);/*Muestra el campo PID del proceso en ejecucion 
en el archivo /proc/[PID]/stat.*/
void mostrar_ppid(char *ptr);/*Muestra el campo PPID del proceso (stat).*/
void mostrar_pgid(char *ptr);/*Muestra el campo PGID del proceso (stat).*/
void mostrar_psid(char *ptr);/*Muestra el campo PSID (session ID) del proceso 
(stat).*/
void mostrar_eip(char *ptr);/*Muestra el estado del Program Counter (registro 
EIP en i386) del procesador antes de ejecutar el proceso actual (stat).*/
void mostrar_esp(char *ptr);/*Muestra el estado del registro de Stack tal como
estaba en el stack del kernel para este proceso en particular (stat).*/
void mostrar_estado(char *ptr);/*Muestra el estado actual del proceso en si
(stat).*/
void mostrar_pri(char *ptr);/*Muestra la prioridad del proceso actual para su 
planificacion (stat).*/
void mostrar_startime(char *ptr);/*Muestra el tiempo transcrurrido desde el 
inicio del sistema en 1/100seg (stat).*/
void mostrar_rss(char *ptr);/*Muestra la cantidad de paginas que el 
proceso tiene realmente en memoria (stat).*/
void mostrar_rlim(char *ptr);/*Muestra el limite en bytes de los recursos de 
memoria para el proceso (tamano de memoria virtual) (stat).*/
void mostrar_sigpend(char *ptr);/*Muestra las signals que el proceso tiene 
pendientes (generalmente 0)(stat).*/
void mostrar_sigblock(char *ptr);/*Muestra las signals que el proceso tiene 
bloqueadas (generalmente 0. Para shells 2) (stat).*/
void mostrar_sigign(char *ptr);/*Muestra las signals que el proceso tiene 
ignoradas (stat).*/
void mostrar_sigcatch(char *ptr);/*Muestra las signals recibidas y procesadas
por el proceso (stat).*/ 
void mostrar_swpages(char *ptr);/*Muestra la cantidad de paginas del proceso 
que fueron swapeadas al disco (stat).*/
void mostrar_cswpages(char *ptr);/*Muestra la cantidad de paginas de los hijos
del proceso que fueron swapeadas al disco (stat).*/
void mostrar_exitsig(char *ptr);/*Muestra la signal emitida por el proceso 
actual al finalizar su ejecucion (stat).*/
void mostrar_addrincod(char *ptr);/*Muestra la direccion de memoria virtual 
arriba de la cual se ubica el area de codigo del proceso en ejecucion (stat).*/
void mostrar_addrficod(char *ptr);/*Muestra la direccion de memoria virtual 
debajo de la cual se ubica el area de codigo del proceso en ejecucion (stat).*/
void mostrar_addrinstk(char *ptr);/*Muestra la direccion de memoria virtual en 
la cual comienza el area de stack del proceso (stat).*/
void pcb();/*Muestra informacion referida al PCB (Process Control Block) de 
un proceso en particular haciendo uso de las funciones declaradas y definidas
en este archivo.*/
void addr_proceso_mv();/*Muestra la ubicacion en memoria virtual del area de 
codigo, datos y stack de un proceso en particular utilizando las funciones 
declaradas en este archivo y las variables globales edata y end.*/


char * proc_lector(const char *str){

    ostringstream oss (ostringstream::out);
    oss << "/proc/" << getpid() << str;
    
    static char buffer[bsize];
    ifstream i_file;
    i_file.open(oss.str().c_str());
    i_file.getline(buffer, bsize, '\n');
    return &buffer[0];
}

int posicion(char *ptr, int cur){

    int k=0, c=0;
    do{
	if(ptr[k]==' ')
	    c++;
	k++;
    }while (*ptr&&c!=cur);
    return k;
}

void show_data(char *ptr, int pos){

    int i=pos;
    do{
    	cout << ptr[i];
	i++;
    }while(ptr[i]!=' '&&i!=pos);
    return;
}
 
void mostrar_comando(char *ptr){

    do{
	cout << ptr ;
	ptr += strlen(ptr)+1;
    }while (*ptr);
    //cout << endl;
return;
}

void mostrar_pid(char *ptr){

    show_data(ptr,0);
    //cout << endl;
return;
}

void mostrar_ppid(char *ptr){

    int k = posicion(ptr,3);
    show_data(ptr,k);   
    cout << endl;
return;
}

void mostrar_pgid(char *ptr){

    int k = posicion(ptr,4);
    show_data(ptr,k);   
    //cout << endl;
return;
}

void mostrar_psid(char *ptr){

    int k = posicion(ptr,5);
    show_data(ptr,k);   
    cout << endl;
return;
}   

void mostrar_eip(char *ptr){

    char str[11];
    int k = posicion(ptr,29);    
    
    int j=0;
    for (int i=k;i<k+11;i++){
    	    str[j] = ptr[i];
	    j++;
    }	
    cout << hex << atoll(str) << endl;
return;
}   

void mostrar_esp(char *ptr){

    char str[11];
    int k = posicion(ptr,28);
    
    int j=0;
    for (int i=k;i<k+11;i++){
    	str[j] = ptr[i];
	j++;
    }	
    cout << hex << atoll(str) << endl;
return;
}   

void mostrar_estado(char *ptr){

    int k = posicion(ptr,2);
    show_data(ptr,k);   
    //cout << endl;
return;
}   
   
void mostrar_pri(char *ptr){

    int k = posicion(ptr,17);
    show_data(ptr,k);   
    //cout << endl;
return;
}   

void mostrar_startime(char *ptr){

    int k = posicion(ptr,21);
    show_data(ptr,k);   
    cout << endl;
return;
}   

void mostrar_rss(char *ptr){

    int k = posicion(ptr,23);
    show_data(ptr,k);
    cout << " paginas.";
    //cout << endl;
return;
}
   
void mostrar_rlim(char *ptr){

    int k = posicion(ptr,24);
    show_data(ptr,k);
    cout << " bytes.";
    cout << endl;
return;
}   

void mostrar_sigpend(char *ptr){

    int k = posicion(ptr,30);
    show_data(ptr,k);
    //cout << endl;
return;
}   

void mostrar_sigblock(char *ptr){

    int k = posicion(ptr,31);
    show_data(ptr,k);
    //cout << endl;
return;
}   

void mostrar_sigign(char *ptr){

    int k = posicion(ptr,32);
    show_data(ptr,k);
    cout << endl;
return;
}   

void mostrar_sigcatch(char *ptr){

    int k = posicion(ptr,33);
    show_data(ptr,k);
    //cout << endl;
return;
}   

void mostrar_swpages(char *ptr){

    int k = posicion(ptr,35);
    show_data(ptr,k);
    //cout << endl;
return;
}
   
void mostrar_cswpages(char *ptr){

    int k = posicion(ptr,36);
    show_data(ptr,k);
    cout << endl;
return;
}
   
void mostrar_exitsig(char *ptr){

    int k = posicion(ptr,37);
    show_data(ptr,k);
    cout << endl;
return;
}   

void mostrar_addrincod(char *ptr){

    char str[15];
    int k = posicion(ptr,25);    
    int j=0;
    for (int i=k;i<k+15;i++){
    	str[j] = ptr[i];
	j++;
    }	
    cout << hex << atoll(str);
return;
}   

void mostrar_addrficod(char *ptr){

    char str[15];
    int k = posicion(ptr,25);    
    int j=0;
    for (int i=k;i<k+15;i++){
    	str[j] = ptr[i];
	j++;
    }	
    cout << hex << atoll(str) << endl;
return;
}   

void mostrar_addrinstk(char *ptr){

    char str[15];
    int k = posicion(ptr,27);    
    int j=0;
    for (int i=k;i<k+15;i++){
    	str[j] = ptr[i];
	j++;
    }
    cout << hex << atoll(str) << endl;
return;
}

void pcb(){
    cout << "IDENTIFICACION" << endl;
    const char *cmdline="/cmdline";
    const char *stat="/stat";
    char *p = proc_lector(cmdline);
    cout << "Comando ejecutado: ";
    mostrar_comando(p);
    p = proc_lector(stat);
    cout << "   Proceso (PID): ";
    mostrar_pid(p);
    cout << "   Proceso padre (PPID): ";
    mostrar_ppid(p);
    cout << "Grupo (PGID): ";
    mostrar_pgid(p);
    cout << "   Sesion (PSID): ";
    mostrar_psid(p);
    /*Muestra la porcion (o parte de ella) de ESTADO del PCB de este proceso.*/
    cout << "\nESTADO DEL PROCESADOR" << endl;
    cout << "Estado del PC (EIP): ";
    mostrar_eip(p);
    cout << "Estado del SP (ESP,kernel stack): ";
    mostrar_esp(p);
    /*Muestra la porcion (o parte de ella) de CONTROL del PCB de este proceso.*/
    cout << "\nCONTROL" << endl;
    cout << "Estado del proceso: ";
    mostrar_estado(p);
    cout << "   Prioridad: ";
    mostrar_pri(p);
    cout << "   Start Time (1/100seg): ";
    mostrar_startime(p);
    cout << "Resid. Set Size (RSS): ";
    mostrar_rss(p);
    cout << "   Lim. de rec. en mem.: ";
    mostrar_rlim(p);
    cout << "Signals pendientes: ";
    mostrar_sigpend(p);
    cout << "   Signals bloqueadas: ";
    mostrar_sigblock(p);
    cout << "   Signals ignoradas: ";
    mostrar_sigign(p);
    cout << "Signals procesadas: ";
    mostrar_sigcatch(p);
    cout << "   Pag. swapeadas: ";
    mostrar_swpages(p);
    cout << "   Pag. swapeadas (hijos): ";
    mostrar_cswpages(p);
    cout << "Signal emitida al final de esta ejecucion: ";
    mostrar_exitsig(p);
    return;
}

void addr_proceso_mv(){
    const char *stat="/stat";
    char *p = proc_lector(stat);
    cout << "\nUBICACION EN MEMORIA VIRTUAL" << endl;
    cout << "Area de Texto: ";
    mostrar_addrincod(p);
    cout << " - ";
    cout << hex << (int64_t)(&etext) << endl;
    cout << "Area de datos:  " << hex << ((int64_t)(&etext) + 1) 
         << " - " << hex << (int64_t)(&edata) << endl;
    cout << "Area de heap:  " << hex << ((int64_t)(&edata) +1 )
         << " - " << hex << (int64_t)(&_end) << endl;
    cout << "Area de stack:  ";
    mostrar_addrinstk(p); 
    cout << endl << endl;
    return;
}

         