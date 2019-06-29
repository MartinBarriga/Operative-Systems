#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>

typedef struct {
	int bandera;
	char contenido[20];
} zona;

zona *buffer;
int id_memory;
int semaforo;
key_t key;

int crearMemoria ();
void eliminarMemoria ();

void crearSemaforos ();
void eliminarSemaforo ();

void productor(int);
const char * obtenerCadena(int);
void consumidor (int);


int main(int argc, char const *argv[]){
	int prod, cons;
	pid_t proceso;
	int *espera;

	buffer = malloc(sizeof(zona));
	buffer->bandera = 0;
	if ( crearMemoria() != -1 ){
		crearSemaforos();
	} 
	else {
		printf("ERROR al crear la llave IPC.\n");
		exit(-1);
	}

	for (int i = 0; i < 20; i++){
		proceso = fork();
		switch (proceso){
			case -1:
				printf("ERROR al crear procesos.\n");
				exit(-1);
			break;

			case 0:
				if ( i%2 == 0 )
				{
					productor(i);
				}
				else
				{
					consumidor(i);
				}
				exit(0);
			break;
			
			default:
			break;
		}
	}

	for (int i = 0; i < 20; i++) wait(espera);
	eliminarSemaforo();
	eliminarMemoria();
	return 0;
}


int crearMemoria (){

	//generamos la llave
	key = ftok ("/bin/ls", 1008);

	if ( key == -1)
		return -1;


    //creamos memoria
	id_memory = shmget(key, sizeof(zona)*5, 0777 | IPC_EXCL | IPC_CREAT);
	if ( id_memory == -1 ){
		id_memory = shmget(key, sizeof(zona)*5, 0777);
		printf("Ligando a la memoria compartida \n");
		buffer = (zona *)shmat(id_memory, (void*)0, 0);
		printf("Ligando la zona de datos a la memoria compartida\n");
		return 0;
	}
	else 
	printf("Se creo la memoria compartida\n");
	

	//ligamos la memoria
	buffer = (zona *)shmat(id_memory, (void*)0, 0);
	printf("Ligando la zona de datos a la memoria compartida\n");

	return 1;
}


void eliminarMemoria(){

	shmdt (buffer);
	printf("Desligando la zona de datos de la memoria compartida.\n");
	
	shmctl (id_memory, IPC_RMID, (struct shmid_ds *)NULL);
	printf("Eliminando el segmento de memoria compartida.\n");
}


void crearSemaforos (){
	
	semaforo = semget (key, 7, 0777 | IPC_EXCL | IPC_CREAT);

	if ( semaforo == -1 )
	{
		semaforo = semget (key, 7, 0777);
	
	} else {
		
		printf("Creando el conjunto de semaforos\n");

		semctl(semaforo, 0, SETVAL, 5);
		semctl(semaforo, 1, SETVAL, 0);
		semctl(semaforo, 2, SETVAL, 1);
		semctl(semaforo, 3, SETVAL, 1);
		semctl(semaforo, 4, SETVAL, 1);
		semctl(semaforo, 5, SETVAL, 1);
		semctl(semaforo, 6, SETVAL, 1);

		printf("Inicializando los semaforos.\n");
	}
}

void eliminarSemaforo (){
	

	//for(int i=0 ; i<7; i++)
	semctl(semaforo, 0, IPC_RMID);
	semctl(semaforo, 1, IPC_RMID);
	semctl(semaforo, 2, IPC_RMID);
	semctl(semaforo, 3, IPC_RMID);
	semctl(semaforo, 4, IPC_RMID);
	semctl(semaforo, 5, IPC_RMID);
	semctl(semaforo, 6, IPC_RMID);
	//eliminarMemoria();
	printf("Eliminando los semaforos.\n");

}

const char * obtenerCadena(int i)
{
	printf("Obtuvimos cadena %d.\n", i);
	if(i == 0) return "aaaaaaaaaaaaaaaaaaaa";
	if(i == 2) return "bbbbbbbbbbbbbbbbbbbb";
	if(i == 4) return "cccccccccccccccccccc";
	if(i == 6) return "dddddddddddddddddddd";
	if(i == 8) return "eeeeeeeeeeeeeeeeeeee";
	if(i == 10) return "ffffffffffffffffffff";
	if(i == 12) return "gggggggggggggggggggg";
	if(i == 14) return "hhhhhhhhhhhhhhhhhhhh";
	if(i == 16) return "iiiiiiiiiiiiiiiiiiii";
	else return "jjjjjjjjjjjjjjjjjjjj";
}

void productor(int i){
	int x = 1;
	printf("Productor %d\n",i);
	int valorSemaforo;
	while (1)
	{
		valorSemaforo = semctl(semaforo, 0, GETVAL);
		if(valorSemaforo >0)
		{
			semctl(semaforo, 0, SETVAL, valorSemaforo-1);
			printf("Se redujo el valor del semaforo 0 en el productor %d.\n", i);

			break;
		}
	}

	while(x)
	{
		for(int j = 0; j<5; j++)
		{
			//sem_wait(j+2);
			valorSemaforo = semctl(semaforo, (j+2), GETVAL);
			printf("%d", valorSemaforo);
			if(valorSemaforo > 0)
			{
				semctl(semaforo, (j+2), SETVAL, valorSemaforo-1);
				printf("Se redujo el valor del semaforo %d en el productor %d para que nadie entre al campo a analizar.\n", (j+2), i);
				if(buffer -> bandera == 0)
				{
					strcpy(buffer -> contenido, obtenerCadena(i));
					buffer -> bandera = 1;
					//sem_signal(j+2);
					valorSemaforo = semctl(semaforo, j+2, GETVAL);
					semctl(semaforo, j+2, SETVAL, valorSemaforo+1);
					printf("Se aumento el valor del semaforo %d en el productor %d.\n", j+2, i);
					x = 0;
					j = 5;
					break;
				}
				//sem_signal(j+2);
				valorSemaforo = semctl(semaforo, j+2, GETVAL);
				semctl(semaforo, j+2, SETVAL, valorSemaforo+1);
				printf("Se aumento el valor del semaforo %d en el productor  %d porque no pudo entrar a un campo.\n", j+2, i);
			}
				
		}
	}
	//sem_signal(c);
	valorSemaforo = semctl(semaforo, 1, GETVAL);
	semctl(semaforo, 1, SETVAL, valorSemaforo+1);
	printf("Se aumento el valor del semaforo 1 en el productor %d para que se pueda consumir.\n", i);
}

void consumidor (int i){
	printf("Consumidor %d\n",i);
	int x = 1;

	int fd1, valorSemaforo;
	char * myfifo1 = "/tmp/myfifo1";
	mkfifo(myfifo1, 0666);
	FILE *Archivo1;
	FILE *Archivo2;
	FILE *Archivo3;
	FILE *Archivo4;
	FILE *Archivo5;
	FILE *Archivo6;
	FILE *Archivo7;
	FILE *Archivo8;
	FILE *Archivo9;
	FILE *Archivo10;

	//sem_wait(c);
	while (1)
	{
		valorSemaforo = semctl(semaforo, 1, GETVAL);
		if(valorSemaforo >0)
		{
			semctl(semaforo, 1, SETVAL, valorSemaforo-1);
			printf("Se redujo el valor del semaforo 1 en el consumidor %d.\n", i);
			break;
		}
	}

	while(x)
	{
		for(int j = 0; j<5; j++ )
		{
			//sem_wait((j+2));

			valorSemaforo = semctl(semaforo, j+2, GETVAL);
			if(valorSemaforo >0)
			{
				semctl(semaforo, j+2, SETVAL, valorSemaforo-1);
				printf("Se redujo el valor del semaforo %d en el consumidor %d.\n", j+2, i);
				if(buffer -> bandera == 1)
				{
					/*pid_t proceso;
					int *espera;
					proceso = fork();
					switch (proceso){
						case -1:
							printf("ERROR al crear procesos.\n");
							exit(-1);
						break;
						case 0:
							fd1 = open(myfifo1, O_RDONLY);
							char ar[20];
							read(fd1, &buffer->contenido, sizeof(buffer->contenido));
					*/
						if(i == 1)
						{
							printf("El consumidor %d introdujo elementos en el archivo1\n", i);
							Archivo1 = fopen ( "Archivo1.txt", "w" );
							fputs(buffer->contenido,Archivo1);
							fclose(Archivo1);
						}
						if(i == 3)
						{
							printf("El consumidor %d introdujo elementos en el archivo2\n", i);
							Archivo2 = fopen ( "Archivo2.txt", "w" );
							fputs(buffer->contenido,Archivo2);
							fclose(Archivo2);
						}
						if(i == 5)
						{
							printf("El consumidor %d introdujo elementos en el archivo3\n", i);
							Archivo3 = fopen ( "Archivo3.txt", "w" );
							fputs(buffer->contenido,Archivo3);
							fclose(Archivo3);
						}
						if(i == 7)
						{
							printf("El consumidor %d introdujo elementos en el archivo4\n", i);
							Archivo4 = fopen ( "Archivo4.txt", "w" );
							fputs(buffer->contenido,Archivo4);
							fclose(Archivo4);
						}
						if(i == 9)
						{
							printf("El consumidor %d introdujo elementos en el archivo5\n", i);
							Archivo5 = fopen ( "Archivo5.txt", "w" );
							fputs(buffer->contenido,Archivo5);
							fclose(Archivo5);
						}
						if(i == 11)
						{
							printf("El consumidor %d introdujo elementos en el archivo6\n", i);
							Archivo6 = fopen ( "Archivo6.txt", "w" );
							fputs(buffer->contenido,Archivo6);
							fclose(Archivo6);
						}
						if(i == 13)
						{
							printf("El consumidor %d introdujo elementos en el archivo7\n", i);
							Archivo7 = fopen ( "Archivo7.txt", "w" );
							fputs(buffer->contenido,Archivo7);
							fclose(Archivo7);
						}
						if(i == 15)
						{
							printf("El consumidor %d introdujo elementos en el archivo8\n", i);
							Archivo8 = fopen ( "Archivo8.txt", "w" );
							fputs(buffer->contenido,Archivo8);
							fclose(Archivo8);
						}
						if(i == 17)
						{
							printf("El consumidor %d introdujo elementos en el archivo9\n", i);
							Archivo9 = fopen ( "Archivo9.txt", "w" );
							fputs(buffer->contenido,Archivo9);
							fclose(Archivo9);
						}
						if(i == 19)
						{
							printf("El consumidor %d introdujo elementos en el archivo10\n", i);
							Archivo10 = fopen ( "Archivo10.txt", "w" );
							fputs(buffer->contenido,Archivo10);
							fclose(Archivo10);
						}
					/*	close (fd1);
						exit(0);
						break;
							
						default:
							fd1 = open(myfifo1,O_WRONLY);
							write(fd1, &(buffer->contenido), sizeof(buffer->contenido));
							close(fd1);
						break;
					}
					wait(espera);*/
					buffer->bandera = 0;
					//sem_signal(j+2);
					valorSemaforo = semctl(semaforo, j+2, GETVAL);
					semctl(semaforo, j+2, SETVAL, valorSemaforo+1);
					printf("Se aumento el valor del semaforo %d en el consumidor %d.\n", j+2, i);
					x = 0;
					j = 5;
					break;
				}
				semctl(semaforo, j+2, SETVAL, valorSemaforo+1);
				printf("Se aumento el valor del semaforo %d en el consumidor %d.\n", j+2, i);
			}
	
		}	
	}
	//sem_signal(p);
	valorSemaforo = semctl(semaforo, 0, GETVAL);
	semctl(semaforo, 0, SETVAL, valorSemaforo+1);
	printf("Se aumento el valor del semaforo 0 en el consumidor %d.\n", i);
						
}