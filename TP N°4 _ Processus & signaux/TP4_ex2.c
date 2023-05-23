#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include <limits.h>
#include<math.h>

int p1, p2 = 0;

int p1_score = 0;
int p2_score = 0;

void sig_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Signal reçu\n");
        
        // Génération d'un nombre aléatoire entre 0 et 1
        int rand_num = rand() % 2;
        
        // Temporisation
        sleep(1);
        
        if (rand_num == 0) {
            // Le joueur manque la balle
            printf("Le joueur manque la balle\n");
        } else {
            // Le joueur renvoie la balle
            printf("Le joueur renvoie la balle\n");
            
            // Incrémentation du score
            if (getpid() == p1) {
                p1_score++;
            } else {
                p2_score++;
            }
        }
        
        // Temporisation supplémentaire
        sleep(1);
        
        // Envoi du signal SIGUSR2 au processus parent
        if (getpid() == p1) {
            kill(p2, SIGUSR2);
        } else {
            kill(p1, SIGUSR2);
        }
    }
    
    if (signum == SIGUSR2) {
        printf("Signal reçu\n");
        
        // Génération d'un nombre aléatoire entre 0 et 1
        int rand_num = rand() % 2;
        
        // Temporisation
        sleep(1);
        
        if (rand_num == 0) {
            // Le joueur manque la balle
            printf("Le joueur manque la balle\n");
        } else {
            // Le joueur renvoie la balle
            printf("Le joueur renvoie la balle\n");
            
            // Incrémentation du score
            if (getpid() == p1) {
                p1_score++;
            } else {
                p2_score++;
            }
        }
        
        // Temporisation supplémentaire
        sleep(1);
        
        // Vérification du score
        if (p1_score >= 13) {
            printf("Joueur 1 a gagné\n");
            kill(p2, SIGTERM);
        }
        
        if (p2_score >= 13) {
            printf("Joueur 2 a gagné\n");
            kill(p1, SIGTERM);
        }
        
        // Envoi du signal SIGUSR1 au processus parent
        if (getpid() == p1) {
            kill(p2, SIGUSR1);
        } else {
            kill(p1, SIGUSR1);
        }
    }
}

int main() {
    srand(time(0));  // Initialisation du générateur de nombres aléatoires
    
    pid_t pid;
    
    // Création du processus fils
    pid = fork();

    // Sauvegarde des PIDs pour la communication entre les processus
    p1 = getpid();
    p2 = pid;
    
    if (pid < 0) {
        perror("Erreur lors de la création du processus fils");
        exit(1);
    }
    
    if (pid == 0) {
        // Processus fils
        signal(SIGUSR1, sig_handler);
        while (1) {
            // Attendre le signal SIGUSR1 du processus parent
            sleep(1);
        }
    } else {
        // Processus père
        signal(SIGUSR2, sig_handler);
        

        
        // Envoi du signal initial SIGUSR1 au processus fils
        kill(pid, SIGUSR1);
        
        while (1) {
            // Attendre le signal SIGUSR2 du processus fils
            sleep(1);
        }
    }
    
    return 0;
}