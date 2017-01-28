#ifndef estructuras
#define estructuras

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  Estructura para procesos
*/
typedef struct proceso {
  long PID;
  char Estado;
  float Tiempo;
  char Comando[32];
  struct proceso *siguiente;
} Proceso;

/*
  Estructura para cola de procesos
*/
typedef struct {
  Proceso *primero;
  Proceso *ultimo;
} cola;

/*
  Estructura para planificador de procesos
*/
typedef struct {
  cola *colas[6];
} EstrucSched;

/*
  Firmas de funciones
*/
Proceso *nuevoProceso(long, char, float, char*);
EstrucSched *Construye(char*);
Proceso *BuscarProceso(EstrucSched*, long);
Proceso *ProxProceso(EstrucSched*);
void ElimProceso(EstrucSched*, long, short);
void ElimProcesoE(EstrucSched*);
void InsertarProceso(EstrucSched*, Proceso*, short);
void TodosProcesosListos(EstrucSched*);
void LeerProceso(EstrucSched*);
void Guardar(EstrucSched*, char*);
void Imprime(EstrucSched*);
void ImprimeCola(cola*);
void ImprimeProceso(Proceso*);

#endif
