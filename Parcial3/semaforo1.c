#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
	//se crea el semaforo
	sem_t *semaforo;

	//se crea un string con el nombre del semaforo
	char *nombreSemaforo = {"semaforo"};

	int *zonaCritica;
	zonaCritica = (int *) malloc(sizeof(int));
	//se inicializa el semaforo
	sem_init(semaforo, 0, 0);
	printf("Tamanio de sem_t: %ld\n", sizeof(sem_t));

	semaforo = sem_open(nombreSemaforo, O_CREAT | O_EXCL, 0666, 1);
	//printf("Id del semaforo %ld\n", semaforo);

	for(int contador = 0; contador <20; contador++)
	{
		sem_wait(semaforo);
		*zonaCritica = contador;
		printf("Productor %d\n", *zonaCritica);
		sem_post(semaforo);
		
	}
	return 0;

}