#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>


void rellenar(int **matriz, int n, int m){
	int i,j;
	for(i = 0; i < n; i++) 
		for(j = 0; j <m; j++) matriz[i][j] = rand() % 4 + 1; 
}

void multiplicar( int **matriz1, int **matriz2, int m1, int m2, int inicio, int fin){
	int resultado,fd,pos=0;
	fd = open(myfifo,O_WRONLY);
	for(int i = inicio; i < fin; i++)
	{
		for(int j = 0; j < m2; j++)
		{
			resultado = 0;
			for(int x = 0; x < m1; x++) 
			{
				resultado  = resultado + (matriz1[i][x] *  matriz2[x][j]);
			}
			
			write(fd, &resultado, sizeof(resultado));
			printf("%d ",resultado);
		}
		printf("\n");
	}
	close(fd);
}

void multiplicarPadre( int **matriz1, int **matriz2, int **matriz3, int m1, int m2, int inicio, int fin){
	int resultado;
	for(int i = inicio; i < fin; i++)
	{
		for(int j = 0; j < m2; j++)
		{
			resultado = 0;
			for(int x = 0; x < m1; x++) 
			{
				resultado  = resultado + (matriz1[i][x] *  matriz2[x][j]);
			}
			matriz3[i][j] = resultado;
			printf("%d ", resultado);
		}
		printf("\n");
	}
}

int main()
{
	int n1, n2, m1, m2, i, j, x,y, nproc, filas, inicio, fin, *espera,resultado,fd;
	pid_t child;
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	// no pedimos el valor de n2, pues ese valor debe ser igual a m1 para que se puedan multiplicar las matrices
	printf("Nota: n es el numero de filas y m es el numero de columnas de la matriz.\n");
	printf("Introduce el valor n de la matriz 1: ");
	scanf("%d", &n1);
	printf("Introduce el valor m de la matriz 1: ");
	scanf("%d", &m1);
	printf("Introduce el valor m de la matriz 2: ");
	scanf("%d", &m2);
	n2 = m1;

	int **matriz1=malloc(sizeof(int*)*n1);
	for (int i = 0; i < n1; ++i)
		matriz1[i]=malloc(sizeof(int)*m1);
	
	int **matriz2=malloc(sizeof(int*)*n2);
	for (int i = 0; i < n2; ++i)
		matriz2[i]=malloc(sizeof(int)*m2);
	
	int **matriz3=malloc(sizeof(int*)*n1);
	for (int i = 0; i < n1; ++i)
		matriz3[i]=malloc(sizeof(int)*m2);


	rellenar(matriz1, n1, m1);
	rellenar(matriz2, n2, m2);		


	printf("\nMatriz1:\n");
	for(i = 0; i < n1; i++)
	{
		for(j = 0; j <m1; j++) printf("%d ", matriz1[i][j]);
		printf("\n");
	}
	printf("\nMatriz2:\n");
	for(i = 0; i < n2; i++) 
	{
		for(j = 0; j <m2; j++) printf("%d ", matriz2[i][j]);
		printf("\n");
	}



	printf("\nIngrese el numero de procesos que van a resolver la multiplicacion: ");
	scanf("%d", &nproc);
	filas = n1/nproc;

	printf("\nProceso padre:\n");
	inicio = 0;
	fin = filas;
	multiplicarPadre(matriz1, matriz2, matriz3, m1, m2, inicio, fin);

	for (int i = 1; i < nproc; i++)
	{
		child = fork();
		switch(child){
			case -1:
				printf("\n No se pudo crear un proceso, la matriz no será multiplicada correctamente.");
				exit(0);
			break;

			case 0:
				printf("Proceso hijo %d:\n", i);
				inicio = i*filas;
				if(i==nproc-1) fin = n1;
				else fin = inicio + filas;
				multiplicar(matriz1, matriz2, m1, m2, inicio, fin);
				exit(0);
			break;

			default:
				inicio = i*filas;
				if(i==nproc-1) fin = n1;
				else fin = inicio + filas;
				fd = open(myfifo, O_RDONLY);
				for(x = inicio; x < fin; x++)
				{
					for(y = 0; y < m2; y++)
					{
						
						read(fd, &resultado, sizeof(resultado));
						matriz3[x][y] = resultado;
					}
					printf("\n");
				}
				close(fd);
			break;
		}
	}
	for (i = 0; i < nproc-1; i++) wait(espera);

	printf("\nProceso padre. Valores en la matriz resultante:\n\n");
	for (i = 0; i < n1; i++)
	{
		for (j = 0; j < m2; j++) printf("%d ",matriz3[i][j]);
		printf("\n");
	}	
	printf("\n");


	return 0;
}

