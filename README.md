# pscheduler
Tarea de Sistemas de Operacion Ene-Mar 2017
Organizacion de los archivos:
  En el archivo main.c se encuentra el menu principal del programa desde el cual
  se selecciona la funcionalidad a realizar en un momento dado y las llamadas a
  las funciones correspondientes.
  En el archivo planificador.c se encuentran las implementaciones de las
  funciones utilizadas por el programa.
  En el archivo estructuras.h se encuentran las definiciones de las estructuras
  que se explicaran más adelante y las firmas de las funciones utilizadas por
  el menu principal.

Estructuras utilizadas:
  Proceso: Se utilizó esta estructura como los nodos de una lista enlazada para
  implementar una cola, adicional al apuntador al siguiente proceso de la cola
  almacena la informacion de cada proceso.
  Cola: Encapsula una cola usando dos apuntadores a procesos, uno para el primer
  proceso y uno para el último proceso.
  EstrucSched: Encapsula todo el planificador de procesos, para ésto almacena
  un arreglo de apuntadores a estructuras de colas de 6 posiciones para ordenar
  los procesos según su prioridad.
