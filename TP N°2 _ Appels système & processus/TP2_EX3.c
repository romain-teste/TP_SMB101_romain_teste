#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

#include<unistd.h>
#include<math.h>


int main(int argc, char* argv[]){


    pid_t f;
    int fd[2], f1;

    f1 = open("/home/teste/null", O_RDWR | O_CREAT);
    
    pipe(fd);

    f = fork();

    if(f == 0){
        close(1);
        dup(f1);

        execlp("ps", "ps", "eaux", NULL);
        execlp("grep", "grep", "^root", NULL);

    }
    else {
        wait(NULL);
        printf("Root est connecté");

    }
}