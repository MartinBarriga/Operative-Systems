#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main()
{
	pid_t proceso;
	int tuberiaPadre[2];
	int tuberiaHijo[2];
	char cadena[50];
	int *espera;
	int i=0;

	if(pipe(tuberiaPadre) == 0){
		printf("Se creo el pipe padre\n");
	}else{
		printf("Error\n");
	}
	if(pipe(tuberiaHijo) == 0){
		printf("Se creo el pipe hijo\n\n");
	}else{
		printf("Error\n");
	}

	proceso = fork();
	
	switch(proceso) {
		case -1:
			printf("Error\n");
		break;

		case 0: 
			while(1){
				close(tuberiaPadre[1]);
				read(tuberiaPadre[0], cadena, sizeof(cadena));
				if(strcmp(cadena, "fin") == 0) break;
				printf("\nPROCESO HIJO. He leeido: %s",cadena);
 				printf("\nPROCESO HIJO.Escribe el mensaje para mandarle al padre: ");
				//fgets(cadena, 50, stdin);
				scanf("%[^\n]", cadena);
				getchar();
				printf("\n");
				close(tuberiaHijo[0]);
				write(tuberiaHijo[1], cadena, sizeof(cadena));
			}

		break;

		default: 
			while(1){
				printf("\nPROCESO PADRE. Escribe el mensaje para mandarle al hijo: ");
				//fgets(cadena, 50, stdin);
				scanf("%[^\n]", cadena);
				getchar();
				printf("\n");
				close(tuberiaPadre[0]);
				write(tuberiaPadre[1], cadena, sizeof(cadena));

				close(tuberiaHijo[1]);
				read(tuberiaHijo[0], cadena, sizeof(cadena));
				if(strcmp(cadena, "fin") == 0) break;
				printf("PROCESO PADRE. He leeido: %s", cadena);
				
			}	
				
		break;			    
	}
		
	return 0;
}