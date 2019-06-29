// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 #include <sys/wait.h>
#include <stdlib.h>
int main()
{
    int fd;
    pid_t proceso;
    int *espera;
    char arr1[80], arr2[80];
    // FIFO file path
    char * myfifo = "/tmp/myfifo";
 
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);
    
    proceso = fork();
        switch(proceso)
        {
            case -1: 
                    printf("Error\n");
            break;

            case 0:
                while(1){
                // First open in read only and read
                fd = open(myfifo,O_RDONLY);
                read(fd, arr1, 80);
                // Print the read string and close
                printf("El padre me dice: %s\n", arr1);
                close(fd);
         
                // Now open in write mode and write
                // string taken from user.
                fd = open(myfifo,O_WRONLY);
                printf("Soy el proceso hijo, escribe el mensaje para el padre: ");
                fgets(arr2, 80, stdin);
               if(strcmp(arr2, "fin") == 0) break;
                write(fd, arr2, strlen(arr2)+1);
                 
                close(fd);
                }
            break;
            default:
                while(1){
                // Open FIFO for write only
                fd = open(myfifo, O_WRONLY);
         
                // Take an input arr2ing from user.
                // 80 is maximum length
                printf("Soy el proceso padre, escribe el mensaje para el hijo: ");
                fgets(arr2, 80, stdin);
                // Write the input arr2ing on FIFO
                // and close it
                if(strcmp(arr1, "fin") == 0) break;
                write(fd, arr2, strlen(arr2)+1);
                 
                close(fd);
         
                // Open FIFO for Read only
                fd = open(myfifo, O_RDONLY);
         
                // Read from FIFO
                read(fd, arr1, sizeof(arr1));
               
                // Print the read message
                printf("El hijo me dice: %s\n", arr1);
                close(fd);
                }
            break;    
        }
    return 0;
}