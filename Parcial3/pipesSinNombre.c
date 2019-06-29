#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main()
{
	pid_t proceso;
	int tuberia[2];
	char cadena[20];
	int *espera;

	if(pipe(tuberia) == 0){
		printf("Se creo el pipe\n");
	}else{
		printf("Error\n");
	}

	proceso = fork();

		switch(proceso) {
			case -1:
				printf("Error\n");
			break;

			case 0: 
				printf("Proceso hijo: %d\n", getpid());
				close(tuberia[1]);
				read(tuberia[0], cadena, sizeof(cadena));
				printf("Hijo lee: %s\n",cadena);
			break;

			default: 
				printf("Proceso padre: %d\n", getpid());
				close(tuberia[0]);
				strcpy(cadena, "mensaje");
				write(tuberia[1], cadena, strlen(cadena));
				
		}

	wait(espera);
	return 0;
}