#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

#include<unistd.h>
#include<math.h>


int main(int argc, char** argv){
    
    pid_t f;
    int status, derNbr;

    f = fork();

    if (f == 0){

        printf("pid: %d, ppid: %d\n", getpid(), getppid());
        status = getpid() % 10;
        printf("%d\n", status);
        exit(status);
    }
    else{
        derNbr = wait(&status);
        printf("pid: %d, pid du fils: %d\n", getpid(), f);
        derNbr %= 10;
        printf("%d\n", derNbr);

    }
    

}