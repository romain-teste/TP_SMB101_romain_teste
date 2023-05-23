#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

#include<unistd.h>
#include<math.h>


int main(int argc, char* argv[]){
    printf("%s\n", argv[1]);
    char* nameBuff;
    pid_t f;
    int fildes = -1;

    int wait_ = 0;

    f = fork();
    int errorClose;

    if (f == 0) {
        printf("test1\n");
        printf("PID du fils: %d\n", getpid());
        printf("test2\n");
        errorClose = close(1);
        printf("test3\n");
        if (errorClose != 0){
            printf("erreur de close() erroClose = %d\n", errorClose);
        }

        nameBuff = "~/tmp/proc-exercise-XXXXXX";

        fildes = mkstemp(nameBuff);
        if(fildes == -1) {
            printf("erreur de mkstemp() fildes = %d\n", fildes);
        }

        //dup2(1, fildes);
        //dprintf(fildes, "numero de descripteur = %d\n", fildes);
        printf("numero de descripteur = %d\n", fildes);


    }
    wait(&wait_);
    printf("PID du pere: %d\n", getpid());
    
    printf("fin du programe\n");

}