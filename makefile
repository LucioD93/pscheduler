all: pscheduler clean

pscheduler: main.o planificador.o estructuras.h
	gcc -o pscheduler main.o planificador.o

main.o: main.c estructuras.h
	gcc -c main.c

planificador.o: planificador.c estructuras.h
	gcc -c planificador.c

clean:
	rm -f *.o
	rm -f *.gch
