#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define SIZE (int)1e5
int tabl[SIZE];
int MAX=0;
int MIN=0;
int CONTEUR=0;

typedef struct my_pthread_data {
  int min;
  int max;
  char buffer[32];
  int* array;
} pthread_data;

int compare(int max, int min){
    if (MIN > min)
    {
        MIN = min;
    }
    if (MAX < max)
    {
        MAX = max;
    }
   return 0;
}

void * my_thred (void * arg){
    pthread_data * data = (pthread_data *) arg;
    int i = data->min;
    int fin = data->max;
    printf("fin = %d", fin);
    int max = data->array[i];
    int min = data->array[i];
 

    printf("debut/fin:%d,%d\n", i, fin);

    while (i <= fin )
    {
 //       tabl[i] = rand() % 1000000 + 1;
 //       printf("%d : %d / %d\n", tabl[i], i, SIZE);
        if (data->array[i] > max)
        {
            max = data->array[i];
        }
        if (data->array[i] < min)
        {
            min = data->array[i];
        }
        i++;
        CONTEUR++;
    }

   // compare(max, min);
    printf("min/max:%d/%d\n",min,max);    
    
    int * return_code = malloc(sizeof(int));
    if (return_code != NULL) {
        *return_code = 1664;
    }
    pthread_exit((void*)return_code);  
}


int main(int argc, char** argv) {
    pthread_t thread_id1; 
    pthread_t thread_id2;
    pthread_t thread_id3;
    pthread_t thread_id4; 
    pthread_t thread_id5; 
    pthread_data my_data1;
    pthread_data my_data2;
    pthread_data my_data3;
    pthread_data my_data4;
    pthread_data my_data5;

    int* array = malloc(SIZE * sizeof(int));

    srand(7);

    for(int i=0; i<SIZE; i++){
        array[i] = rand();
        printf("array[%7d]=%d\n", i, array[i]);
    }



    int * my_return_code;
    int ecart = SIZE / 5;
    my_data1.min=0;
    my_data1.max=ecart;
    my_data1.array=array;
    int ret1 =  pthread_create(&thread_id1, NULL, &my_thred, &my_data1);

    my_data2.min=ecart + 1;
    my_data2.max=ecart * 2;
    my_data2.array=array;
    int ret2 =  pthread_create(&thread_id2, NULL, &my_thred, &my_data2);

    my_data3.min=ecart * 2 + 1;
    my_data3.max=ecart * 3;
    my_data3.array=array;
    int ret3 =  pthread_create(&thread_id3, NULL, &my_thred, &my_data3);

    my_data4.min=ecart * 3 + 1;
    my_data4.max=ecart * 4;
    my_data4.array=array;
    int ret4 =  pthread_create(&thread_id4, NULL, &my_thred, &my_data4);

    my_data5.min=ecart * 4 + 1;
    my_data5.max=SIZE;
    my_data5.array=array;
    int ret5 =  pthread_create(&thread_id5, NULL, &my_thred, &my_data5);

    if (ret1 != 0) {
        perror("Impossible de créer le thread");
    }
    else {
        pthread_join(thread_id1, (void**)&my_return_code);
        pthread_join(thread_id2, (void**)&my_return_code);
        pthread_join(thread_id3, (void**)&my_return_code);
        pthread_join(thread_id5, (void**)&my_return_code);

        printf("fin du code MAX=%d, MIN=%d\n", MAX, MIN);
        printf("COMPTEUR=%d\n", CONTEUR);
        printf("ecart=%d\n", ecart);
    }

    
    return 0;
}