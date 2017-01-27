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
    printf("0) Guardar y salir\n");
    printf("Solo se toma el primer caracter: >");
    scanf("%d", &opcion);
      switch (opcion) {
        case 1:
        Imprime(s);
        break;
        case 2:
        printf("Planificar proximo proceso\n");
        //ProxProceso(s);
        break;
        case 3:
          printf("Estoy listo estoy listo\n");
          TodosProcesosListos(s);
        break;
        case 0:
        printf("Salgo\n");
        Guardar(s, argv[2]);
        exit(0);
        break;
        default:
        printf("Intente de nuevo\n");
        break;
      }
  }
  return 0;
}
