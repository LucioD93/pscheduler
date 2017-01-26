#include "estructuras.h"

// Funcion para insertar un proceso en una cola
void InsertarProcesoEnCola(cola *c, Proceso *p) {
  if (!c -> primero) {
    c -> primero = p;
    c -> ultimo = p;
  }
  else {
    c -> ultimo -> siguiente = p;
    c -> ultimo = p;
  }
}

// Funcion para determinar si una cola esta vacia
int ColaVacia(cola *c) {
  return (c -> primero == NULL);
}

// Funcion para obtener el primer proceso en una cola
Proceso *PrimeroEnCola(cola *c) {
  return c -> primero;
}

// Funcion para insertar un proceso en un planificador de procesos
void InsertarProceso(EstrucSched *s, Proceso *p, short prioridad) {
  if (prioridad < 0 || prioridad > 5) {
    printf("ERROR: prioridad debe estar entre 0 y 5\n");
    exit(1);
  }
  InsertarProcesoEnCola(s -> colas[prioridad], p);
}

// Funcion para generar un nuevo proceso
Proceso *nuevoProceso(long pid, char estado, float tiempo, char comando[32]) {
  if (pid <= 0) {
    printf("ERROR: PID debe ser positivo\n");
    exit(1);
  }
  if (tiempo < 0) {
    printf("ERROR: tiempo debe ser no negativo");
    exit(1);
  }
  if (estado != 'L' && estado != 'E') {
    printf("ERROR: estado solo puede ser L o E\n");
    exit(1);
  }
  Proceso *p = (Proceso*) malloc(sizeof(Proceso));
  p -> PID = pid;
  p -> Estado = estado;
  p -> Tiempo = tiempo;
  strcpy(p -> Comando, comando);
  p -> siguiente = NULL;
  return p;
}

// Funcion para cambiar el estado de un proceso
void CambiarEstado(EstrucSched *s, Proceso *p, char newestado) {
  
}

// Funcion para poner todos los procesos en estado listo

// Funcion para planificar el proximo proceso


//Funcion para eliminar el proceso en ejecucion
void ElimProcesoE(EstrucSched *s) {
  Proceso *actual;
  Proceso *previo;
  for (int i = 0; i < 6; i++) {
    actual = s -> colas[i] -> primero;
    if (actual -> Estado == 'E') {
      s -> colas[i] -> primero = actual -> siguiente;
      free(actual);
    } else {

    }
  }
}

// Funcion para crear un nuevo planificador leyendo un archivo
EstrucSched *Construye(char *filename) {
  // Se inicializa el planificador de procesos
  EstrucSched *planificador = (EstrucSched*) malloc(sizeof(EstrucSched));
  for (int i = 0; i < 6; i++) {
    planificador -> colas[i] = (cola*) malloc(sizeof(cola));
    planificador -> colas[i] -> primero = NULL;
    planificador -> colas[i] -> ultimo = NULL;
  }
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    printf("ERROR: No se puede abrir el archivo de entrada\n");
    exit(1);
  }
  long pid;
  char estado;
  int prioridad;
  float tiempo;
  char comando[32];
  Proceso *p;
  while(1) {
    fscanf(f, "%ld", &pid);
    if(feof(f)) {
      break;
    }
    fgets(&estado, 2, f);
    fgets(&estado, 2, f);
    fscanf(f, "%d", &prioridad);
    fscanf(f, "%f", &tiempo);
    fscanf(f, "%s", comando);
    p = nuevoProceso(pid, estado, tiempo, comando);
    InsertarProceso(planificador, p, prioridad);
  }
  fclose(f);
  return planificador;
}

// Funcion para buscar un proceso por su PID
Proceso *BuscarProceso(EstrucSched *s, long pidBuscado) {
  Proceso *actual;
  for(int i = 0; i < 6; i++) {
    actual = s -> colas[i] -> primero;
    while (actual) {
      if (actual -> PID == pidBuscado) {
        return actual;
      }
      actual = actual -> siguiente;
    }
  }
  return NULL;
}

// Funcion para leer un proceso de teclado y agregarlo a un planificador
void LeerProceso(EstrucSched *s){
  long pid;
  char estado = ' ';
  int prioridad;
  float tiempo;
  char *comando;
  printf("Introduce el pid del nuevo proceso: ");
  scanf("%ld", &pid);
  printf("PID: |%ld|\n", pid);
  printf("Introduce el estado del nuevo proceso (Solo se acepta 'L' y 'E'): ");
  printf("Deberia leer el estado|");
  scanf("%c", &estado);
  printf("|Debi leer el proceso |%c|", estado);
  printf("Introduce la prioridad del nuevo proceso (del 0 al 5): ");
  scanf("%d", &prioridad);
  printf("Introduce el tiempo de ejecucion del nuevo proceso: ");
  scanf("%f", &tiempo);
  printf("Introduce el nombre del nuevo proceso: ");
  scanf("%s\n", comando);
  Proceso *nuevo = nuevoProceso(pid, estado, tiempo, comando);
  InsertarProceso(s, nuevo, prioridad);

}

// Funcion para imprimir un planificador en un archivo
void Guardar(EstrucSched *s, char *archivo) {
  FILE *f = fopen(archivo, "w");
  if (f == NULL) {
    printf("ERROR: No se pudo abrir el archivo de salida\n");
    exit(1);
  }
  for(int i = 0; i< 6; i++) {
    fprintf(f, "Q%d\n", i);
    Proceso *actual = s-> colas[i] -> primero;
    if (actual) {
      Proceso *siguiente = actual -> siguiente;
      while (siguiente) {
        fprintf(f, "pid:%ld, estado:%c, tiempo:%f, comando:%s\n", actual -> PID, actual -> Estado, actual -> Tiempo, actual -> Comando);
        free(actual);
        actual = siguiente;
        siguiente = siguiente -> siguiente;
      }
      fprintf(f, "pid:%ld, estado:%c, tiempo:%f, comando:%s\n", actual -> PID, actual -> Estado, actual -> Tiempo, actual -> Comando);
      free(actual);
    }
    fprintf(f, "-------------\n");
    free(s -> colas[i]);
  }
  fclose(f);
  free(s);
}

// Funcion para mostrar por consola un planificador de procesos
void Imprime(EstrucSched *s) {
  for (int i = 0; i < 6; i++) {
    printf("Q%d\n", i);
    ImprimeCola(s -> colas[i]);
    printf("---------------\n");
  }
}

// Funcion para imprimir los procesos en una cola
void ImprimeCola(cola *c) {
  Proceso *actual = c -> primero;
  while (actual) {
    ImprimeProceso(actual);
    actual = actual -> siguiente;
  }
}

// Funcion para imprimir un proceso
void ImprimeProceso(Proceso *p) {
  printf("PID: %ld, Estado: %c, Tiempo: %f, Comando: %s\n", p -> PID, p -> Estado, p -> Tiempo, p -> Comando);
}