#include "estructuras.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Error en los argumentos de entrada, se necesitan 2 argumentos\n");
    exit(1);
  }
  EstrucSched *s = Construye(argv[1]);
  int opcion;
  while(1) {
    printf("-----------------\n");
    printf("Elija una opcion\n");
    printf("1) Imprimir los procesos en el planificador\n");
    printf("2) Planificar proximo proceso\n");
    printf("3) Cambiar todos los procesos a estado listo\n");
    printf("4) Eliminar proceso en ejecucion\n");
    printf("0) Guardar y salir\n");
    printf("Solo se toma el primer caracter: >");
    scanf("%d", &opcion);
      switch (opcion) {
        case 1:
        Imprime(s);
        break;
        case 2:
        TodosProcesosListos(s);
        printf("Planificar proximo proceso: ");
        ImprimeProceso(ProxProceso(s));
        break;
        case 3:
          TodosProcesosListos(s);
        break;
        case 4:
          ElimProcesoE(s);
        break;
        case 0:
        printf("Salgo\n");
        Guardar(s, argv[2]);
        exit(0);
        break;
        default:
        printf("ERROR: Intente de nuevo\n");
        break;
      }
  }
  return 0;
}
