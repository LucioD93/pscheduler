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
Proceso *nuevoProceso(long pid, Estado estado, float tiempo, char comando[32]) {
  if (pid <= 0) {
    printf("ERROR: PID debe ser positivo\n");
    exit(1);
  }
  if (tiempo < 0) {
    printf("ERROR: tiempo debe ser no negativo");
    exit(1);
  }
  Proceso *p = (Proceso*) malloc(sizeof(Proceso));
  if (!p) {
    printf("ERROR: No se ha podido reservar espacio para proceso\n");
    exit(1);
  }
  p -> PID = pid;
  p -> estado = estado;
  p -> Tiempo = tiempo;
  strcpy(p -> Comando, comando);
  p -> siguiente = NULL;
  return p;
}

// Funcion para cambiar el estado de un proceso
void CambiarEstado(EstrucSched *s, Proceso *p, Estado newestado) {
  p -> estado = newestado;
}

// Funcion para poner todos los procesos en estado listo
void TodosProcesosListos( EstrucSched *s) {
  Proceso *actual;
  for (int i = 0; i < 6; i++) {
    actual = s -> colas[i] -> primero;
    while (actual) {
      CambiarEstado(s, actual, L);
      actual = actual -> siguiente;
    }
  }
}

// Funcion para planificar el proximo proceso
Proceso *ProxProceso(EstrucSched *s) {
  int i = 0;
  while( i < 6 && ColaVacia(s -> colas[i])) {
    i++;
  }
  if (i == 6) {
    return NULL;
  }
  // Si llego aqui encontro una cola no vacia
  Proceso *p = s -> colas[i] -> primero;
  CambiarEstado(s, p, E);
  if (p -> siguiente) {
    s -> colas[i] -> primero = p -> siguiente;
    p -> siguiente = NULL;
    s -> colas[i] -> ultimo -> siguiente = p;
    s -> colas[i] -> ultimo = p;
  }
  return p;

}

// Funcion para crear un nuevo planificador leyendo un archivo
EstrucSched *Construye(char *filename) {
  // Se inicializa el planificador de procesos
  EstrucSched *planificador = (EstrucSched*) malloc(sizeof(EstrucSched));
  if (!planificador) {
    printf("ERROR: No se ha podido reservar espacio para el planificador\n");
    exit(1);
  }
  for (int i = 0; i < 6; i++) {
    planificador -> colas[i] = (cola*) malloc(sizeof(cola));
    if(!planificador -> colas[i]) {
      printf("ERROR: No se ha podido reservar espacio para cola[%d]\n", i);
    }
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
  Estado e;
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
    e = CharAEstado(estado);
    p = nuevoProceso(pid, e, tiempo, comando);
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

// Funcion para eliminar un proceso en ejecucion de una cola
void EliminarEnEjecucion(cola *c) {
  if(ColaVacia(c)) {
    return;
  }
  Proceso *p;
  if (c -> primero -> estado == E) {
    p = c -> primero;
    c -> primero = p -> siguiente;
    free (p);
    return;
  }
  Proceso *previo;
  previo = c -> primero;
  p = previo -> siguiente;
  while (p && p -> estado == L) {
    previo = p;
    p = p -> siguiente;
  }
  if (p) {
    previo -> siguiente = p -> siguiente;
    free(p);
  }
}

// Funcion para recuperar el apuntador al ultimo elemento de una cola
void RecuperarUltimo(cola *c) {
  if (!ColaVacia(c)) {
    Proceso *p = c -> primero;
    while (p) {
      c -> ultimo = p;
      p = p -> siguiente;
    }
  } else {
  }
}

// Funcion para eliminar un proceso de una cola teniendo su pid
void EliminarPorPID(cola *c, long pid) {
  if (ColaVacia(c)) {
    return;
  }
  Proceso *p;
  if (c -> primero -> PID == pid) {
    p = c -> primero;
    c -> primero = p -> siguiente;
    free (p);
    return;
  }
  Proceso *previo;
  previo = c -> primero;
  p = previo -> siguiente;
  while (p && p -> PID != pid) {
    previo = p;
    p = p -> siguiente;
  }
  if (p) {
    previo -> siguiente = p -> siguiente;
    free(p);
  }
}

// Funcion para eliminar un proceso del planificador teniendo su pid y su prioridad
void ElimProceso(EstrucSched *s, long pid, short prioridad) {
  EliminarPorPID(s -> colas[prioridad], pid);
  RecuperarUltimo(s -> colas[prioridad]);
}

// Funcion para eliminar el proceso en ejecucion
void ElimProcesoE(EstrucSched *s) {
  for (int i = 0; i < 6; i++) {
    EliminarEnEjecucion(s -> colas[i]);
    RecuperarUltimo(s -> colas[i]);
  }
}

// Funcion para leer un proceso de teclado y agregarlo a un planificador
void LeerProceso(EstrucSched *s){
  long pid;
  char estado = ' ';
  Estado e;
  int prioridad;
  float tiempo;
  char comando[32];
  char *c;
  printf("Introduce el pid del nuevo proceso: ");
  scanf("%ld", &pid);
  printf("Introduce el estado del nuevo proceso (Solo se acepta 'L' y 'E'): ");
  scanf(" %c", &estado);
  e = CharAEstado(estado);
  printf("Introduce la prioridad del nuevo proceso (del 0 al 5): ");
  scanf("%d", &prioridad);
  printf("Introduce el tiempo de ejecucion del nuevo proceso: ");
  scanf("%f", &tiempo);
  printf("Introduce el nombre del nuevo proceso: ");
  scanf("%s", comando);
  c = (char*) comando;
  Proceso *nuevo = nuevoProceso(pid, e, tiempo, c);
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
    fprintf(f, "Prioridad: %d\n", i);
    Proceso *actual = s-> colas[i] -> primero;
    if (actual) {
      Proceso *siguiente = actual -> siguiente;
      while (siguiente) {
        fprintf(f, "PID: %ld, Estado: %c, Tiempo: %f, Comando: %s\n", actual -> PID, EstadoAChar(actual -> estado), actual -> Tiempo, actual -> Comando);
        free(actual);
        actual = siguiente;
        siguiente = siguiente -> siguiente;
      }
      fprintf(f, "PID: %ld, Estado: %c, Tiempo: %f, Comando: %s\n", actual -> PID, EstadoAChar(actual -> estado), actual -> Tiempo, actual -> Comando);
      free(actual);
    }
    fprintf(f, "#################################################################\n");
    free(s -> colas[i]);
  }
  fclose(f);
  free(s);
}

// Funcion para mostrar por consola un planificador de procesos
void Imprime(EstrucSched *s) {
  for (int i = 0; i < 6; i++) {
    printf("Prioridad: %d\n", i);
    ImprimeCola(s -> colas[i]);
    printf("#################################################################\n");
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

// Funcion para pasar de char a Estado
Estado CharAEstado(char e) {
  switch (e) {
    case 'E':
      return E;
    break;
    default:
      return L;
    break;
  }
}

// Funcion para pasar de Estado a char
char EstadoAChar(Estado e) {
  switch (e) {
    case L:
      return 'L';
    break;
    case E:
      return 'E';
    break;
    default:
      return ' ';
    break;
  }
}

// Funcion para imprimir un proceso
void ImprimeProceso(Proceso *p) {
  if (!p) {
    printf("Proceso nulo\n");
    return;
  }
  printf("PID: %ld, Estado: %c, Tiempo: %f, Comando: %s\n", p -> PID, EstadoAChar(p -> estado), p -> Tiempo, p -> Comando);
}
