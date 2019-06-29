#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//Es necesario tener instalado el open cv y compiar de la siguiente forma:
//g++ $(pkg-config --cflags --libs opencv) Practica3Imagen.cpp -o Practica3Imagen
int main()
{
	int i, *espera,fd1,fd2,fd3;
	char * myfifo1 = "/tmp/myfifo1";
	char * myfifo2 = "/tmp/myfifo2";
	char * myfifo3 = "/tmp/myfifo3";
	pid_t proceso;
	mkfifo(myfifo1, 0666);
	mkfifo(myfifo2, 0666);
	mkfifo(myfifo3, 0666);
	
	Mat img1;
	Mat img2;
	Mat img3;
	

	//obtenemos la imagen
	img1 = imread("imagen.jpg", WINDOW_AUTOSIZE);
	img2 = imread("imagen.jpg", WINDOW_AUTOSIZE);
	img3 = imread("imagen.jpg", WINDOW_AUTOSIZE);

	
	for(i = 0; i<3; i++)
	{
		proceso = fork();
		switch(proceso){
			case -1:
				printf("\n No se pudo crear un proceso.");
				exit(0);
			break;
			case 0:
				if(i == 0)
				{
					fd1 = open(myfifo1, O_RDONLY);
					read(fd1, &img1, sizeof(img1));
					for(int y=0;y<img1.rows;y++)
					{
					    for(int x=0;x<img1.cols;x++)
					    { 
					    	//Obtenemos el pixel
					    	Vec3b color = img1.at<Vec3b>(Point(x,y));
					    	//Modificamos el color
					      	
					            color[1] = 0;
					            color[2] = 0;				            
					       	
					       	
					       	//guardamos el pixel con el color modificado
					       	img1.at<Vec3b>(Point(x,y)) = color;
					    }
					}
					imwrite("azul.jpg", img1);
					close(fd1);
				}
				else if(i == 1)
				{
					fd2 = open(myfifo2, O_RDONLY);
					read(fd2, &img2, sizeof(img2));
					for(int y=0;y<img2.rows;y++)
					{
					    for(int x=0;x<img2.cols;x++)
					    { 
					    	//Obtenemos el pixel
					    	Vec3b color = img2.at<Vec3b>(Point(x,y));
					    	//Modificamos el color
					    	
					       		color[0] = 0;
					            color[1] = 0;
					       	
					       						       	//guardamos el pixel con el color modificado
					       	img2.at<Vec3b>(Point(x,y)) = color;
					    }
					}
					imwrite("rojo.jpg", img2);
					close(fd2);

				}
				else{
					fd3 = open(myfifo3, O_RDONLY);
					read(fd3, &img3, sizeof(img3));
					for(int y=0;y<img3.rows;y++)
					{
					    for(int x=0;x<img3.cols;x++)
					    { 
					    	//Obtenemos el pixel
					    	Vec3b color = img3.at<Vec3b>(Point(x,y));
					    	//Modificamos el color
					      	
					       	
					       		color[2] = 0;
					            color[0] = 0;
					       	
					       	//guardamos el pixel con el color modificado
					       	img3.at<Vec3b>(Point(x,y)) = color;
					    }
					}
					imwrite("verde.jpg", img3);
					close(fd3);

				}
				
				
				exit(0);
			break;
			default:

				if(i==0) {
					
					fd1 = open(myfifo1,O_WRONLY);
					write(fd1, &img1, sizeof(img1));
					close(fd1);
					
				}
				else if(i ==1){ 
					
					fd2 = open(myfifo2,O_WRONLY);
					write(fd2, &img2, sizeof(img2));
					close(fd2);
				}
				else{ 
					
					fd3 = open(myfifo3,O_WRONLY);
					write(fd3, &img3, sizeof(img3));
					close(fd3);
				}
				
				

			break;	
		}
	}
	for (int i = 0; i < 3; i++) wait(espera);
	return 0;
}