#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include <limits.h>
#include<unistd.h>
#include<math.h>

int COMPTEUR = 0;
int CONTINU = 1;

void compte(int argc){
    COMPTEUR++;
    printf("%d\n", COMPTEUR);
}

void stopAct(int argc){
    CONTINU = 0;
}

int main(int argc, char* argv[]){
    pid_t pid =0;
    //int i=2;
    sigset_t sig_proc;
    sigemptyset(&sig_proc);
    struct sigaction info, stop;
    info.sa_handler=compte;
    info.sa_mask=sig_proc;
    info.sa_flags=0;

    stop.sa_handler=compte;
    stop.sa_mask=sig_proc;
    stop.sa_flags=0;

    sigaction(SIGINT, &stop, NULL);


    if(sigaction(SIGINT, &info, NULL) != 0){
        //error...
    }
    while (CONTINU)
    {
        sleep(10);
        
    }
    
}