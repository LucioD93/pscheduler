#ifndef estructuras
#define estructuras

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  Enumerado para los estados de los procesos
*/
typedef enum {L, E} Estado;

/*
  Estructura para procesos
*/
typedef struct proceso {
  long PID;
  Estado estado;
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
EstrucSched *Construye(char*);
Proceso *nuevoProceso(long, Estado, float, char*);
Proceso *BuscarProceso(EstrucSched*, long);
Proceso *ProxProceso(EstrucSched*);
Estado CharAEstado(char);
char EstadoAChar(Estado);
void CambiarEstado(EstrucSched*, Proceso*, Estado);
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
