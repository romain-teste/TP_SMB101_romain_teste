#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<getopt.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include <string.h>
#define size 100

int main(int argc, char *argv[]) {

    char var [size];
    if (argc <= 1){
        scanf("%s", var);
    } else {
        strcpy(var, argv[1]);
    }
    printf("%s", var);
    int fp, fpc;
    fp = open(var, O_RDONLY);
    fpc = open("testCopie.txt", O_WRONLY|O_CREAT); 

    if (fp >= 0 && fpc != 0) {
        int octetsLire, octetsLu;
        int octetsEcrit;

        char* buffer = (char *) malloc(sizeof(char)*4096);
        char* revBuffer;
        int cont=0;
        while (octetsLu = read(fp, buffer, 4096)){
            cont += 1;
        
            //iseek (fp, buffer, SEEK_CUR);
            octetsEcrit = write(fpc, buffer, octetsLu);
            
            if(octetsEcrit != octetsLu){
                perror("Erreur d'écriture");
                exit(1);
            }
            if(octetsLu != 4096){
                printf("EOF\n");
            }
        }
        printf("%d", cont);
        // libération des descripteurs
        close(fp);
        close(fpc);
        // libération de la mémoire
        free(buffer);
    }else {
        printf("%d\n", fp);
        printf("%d", fpc);
    }
    
  return EXIT_SUCCESS;
}

